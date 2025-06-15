#include "game.h"

#include <mutex>
#include <exception>

#include "common/model/vector_2d.h"
#include "common/periodic_clock.h"
#include "server/events/overloaded.h"

void Game::handle_use_weapon(const uint8_t& player_id) {
    if (this->state != GameState::Playing) return;
    auto it = players.find(player_id);
    if (it == players.end()) return;
    gamelogic.start_using_weapon(it->second, round);
}

void Game::handle_stop_using_weapon(const uint8_t& player_id) {
    auto it = players.find(player_id);
    if (it == players.end()) return;
    gamelogic.stop_using_weapon(it->second);
}

void Game::handle_switch_weapon(const uint8_t& player_id, const SwitchWeaponEvent& event) {
    auto it = players.find(player_id);
    if (it != players.end()) {
        it->second.equip_weapon_by_type(event.get_slot_id());
    }
}

void Game::handle_buy_weapon(const uint8_t& player_id, const BuyEvent& event) {
    if (state != GameState::Playing) return;

    auto it = players.find(player_id);
    if (it == players.end()) return;
    gamelogic.buy_weapon(it->second, event.get_weapon_id(), round);
}

void Game::handle_leave_game(const uint8_t& player_id) {
    // TODO: Check game/round state
    auto it = players.find(player_id);
    if (it != players.end()) {
        round.notify_on_one_player_less(it->second.get_team());
    }
    players.erase(it);
    auto queue_it = client_queues.find(player_id);
    client_queues.erase(queue_it);
}

void Game::handle_movement(const uint8_t& player_id, const MovementEvent& event) {
    auto it = players.find(player_id);
    if (it != players.end()) {
        it->second.update_movement_direction_by_merge(event.get_direction());
    }
}

void Game::handle_stop_movement(const uint8_t& player_id, const StopMovementEvent& event) {
    auto it = players.find(player_id);
    if (it != players.end()) {
        if (event.is_movement_horizontal()) {
            it->second.stop_horizontal_movement();
        } else {
            it->second.stop_vertical_movement();
        }
    }
}

void Game::handle_rotation(const uint8_t& player_id, const RotationEvent& event) {
    auto it = players.find(player_id);
    if (it != players.end()) {
        it->second.set_angle(event.get_angle_in_degrees());
    }
}

// TODO: Update GameManager so this is not needed
void Game::handle_pick_role(const uint8_t player_id, const PickRoleEvent& event) {
    auto it = players.find(player_id);
    if (it != players.end()) {
        it->second.set_role_id(event.get_role_id());
    }
}

void Game::handle(uint8_t player_id, const GameEventVariant& event) {
    std::visit(
            overloaded{[player_id, this](const MovementEvent& e) { handle_movement(player_id, e); },
                       [player_id, this](const StopMovementEvent& e) { handle_stop_movement(player_id, e); },
                       [player_id, this](const LeaveGameEvent&) { handle_leave_game(player_id); },
                       [player_id, this](const QuitEvent&) { handle_leave_game(player_id); },
                       [player_id, this](const RotationEvent& e) { handle_rotation(player_id, e); },
                       [player_id, this](const PickRoleEvent& e) { handle_pick_role(player_id, e); },
                       [player_id, this](const SwitchWeaponEvent& e) { handle_switch_weapon(player_id, e); },
                       [player_id, this](const BuyEvent& e) { handle_buy_weapon(player_id, e); },
                       [this](const DropWeaponEvent&) {},
                       [player_id, this](const UseWeaponEvent&) {handle_use_weapon(player_id); }, 
                       [player_id, this](const StopUsingWeaponEvent&) {handle_stop_using_weapon(player_id); }, 
                       [this](const DefuseBombEvent&) {},
                       [this](const ReloadWeaponEvent&) {}, [this](const BuyAmmoEvent&) {}},
            event);
}

void Game::clear_game_queue() {
    std::pair<uint8_t, GameEventVariant> event_info;
    while (game_queue.try_pop(event_info)) ;
}

// Resets players
void Game::start_new_round() {
    state = GameState::Playing;

    int ct_count = 0;
    int tt_count = 0;

    for (auto& [id, player] : players) {
        player.reset_for_new_round();
        handle_stop_using_weapon(id);
        if (player.get_team() == Model::TeamID::CT) ct_count++;
        else tt_count++;
    }
    std::cout << "NUEVA RONDA" << std::endl;
    round.set_ct_count(ct_count);
    round.set_tt_count(tt_count);

    // round = new_buying_round();
    round.to_buying_phase();
}

void Game::update_players_that_won() {
    Model::TeamID winner = round.get_winner_team();

    if (winner == Model::TeamID::NONE) return;

    if (winner == Model::TeamID::CT) {
        ct_rounds_won++;
    } else if (winner == Model::TeamID::TT) {
        tt_rounds_won++;
    }

    for (auto& [player_id, player] : players) {
        if (player.get_team() == winner) {
            player.add_money(1000);
        }
    }
}

void Game::process_frames(uint16_t frames_to_process) {
    movement_system.process_movements(players, frames_to_process);
    round.update(frames_to_process);
    gamelogic.process_shooting(players, round, frames_to_process);

    if (round.ended()) {
        clear_game_queue();
        update_players_that_won();

        if (round.get_count_of_rounds() == MAX_ROUNDS) {
            state = GameState::Finished;
            is_not_finished = false;
            return;
        }

        start_new_round();
    }
}

void Game::broadcast_game_state() {
    std::vector<DTO::PlayerDTO> player_dtos;
    for (const auto& [id, player] : players) {
        player_dtos.push_back(player.to_dto());
    }

    DTO::RoundDTO round_dto = round.to_dto(GAME_FPS);

    Model::TeamID winner = Model::TeamID::NONE;
    bool ended = (state == GameState::Finished);
    if (ended) {
        if (ct_rounds_won > tt_rounds_won) winner = Model::TeamID::CT;
        else if (tt_rounds_won > ct_rounds_won) winner = Model::TeamID::TT;
    }

    DTO::GameStateDTO game_snapshot(
        state,
        player_dtos,
        ended,
        winner,
        round_dto,
        ct_rounds_won,
        tt_rounds_won
    );

    for (auto& [id, queue]: client_queues) {
        try {
            queue->push(game_snapshot);
        } catch (const ClosedQueue&) {}
    }
}

void Game::update_game_with_events() {
    std::pair<uint8_t, GameEventVariant> event_info;
    try {
        while (game_queue.try_pop(event_info)) {
            uint8_t player_id = event_info.first;
            GameEventVariant event = event_info.second;
            handle(player_id, event);
        }
    } catch (const ClosedQueue&) {}
}

void Game::tick(uint16_t frames_to_process) {
    std::lock_guard<std::mutex> lock(mutex);
    if (frames_to_process > 1) {
        process_frames(frames_to_process - 1);
    }

    update_game_with_events();
    process_frames();
    broadcast_game_state();
}

void Game::close() {
    kill();
    game_queue.close();
    join();
}

Game::Game(const std::string& party_name, const std::string& map_name)
: party_name(party_name), map_name(map_name) {
    start();
}

uint8_t Game::get_number_of_players() {
    std::lock_guard<std::mutex> lock(mutex);
    return players.size();
}

std::string Game::get_party_name() {
    std::lock_guard<std::mutex> lock(mutex);
    return party_name;
}

std::string Game::get_map_name() {
    std::lock_guard<std::mutex> lock(mutex);
    return map_name;
}

GameQueue& Game::get_queue() {
    std::lock_guard<std::mutex> lock(mutex);
    return game_queue;
}

bool Game::is_dead() {
    std::lock_guard<std::mutex> lock(mutex);
    return !is_not_finished;
}

// FALTA: ESTO ESTA ARRANCANDO LA RONDA CON 1 SOLO PLAYER, QUE EVENTUALMENTE GANARÍA TODO Y TERMINA
uint8_t Game::add_player(
    const std::string& username,
    ClientQueue& client_queue,
    Model::TeamID team_id,
    Model::RoleID role_id
) {
    std::lock_guard<std::mutex> lock(mutex);

    if (state != GameState::WaitingStart) {
        return -1;
    }

    const uint8_t new_id = next_player_id++;
    players.emplace(new_id, FullPlayer(new_id, username, team_id, role_id));
    client_queues[new_id] = &client_queue;

    round.notify_player_joined(team_id);

    return new_id;
}

void Game::kill() {
    std::lock_guard<std::mutex> lock(mutex);
    is_not_finished = false;
}

void Game::run() {
    PeriodicClock clock(GAME_FPS); 

    while (is_not_finished) {
        uint16_t frames_to_process = clock.sleep_and_get_frames();
        this->tick(frames_to_process);
    }
}

Game::~Game() {
    close();
}
