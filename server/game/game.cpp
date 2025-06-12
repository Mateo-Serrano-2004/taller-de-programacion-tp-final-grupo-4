#include "game.h"

#include <mutex>
#include <exception>

#include "common/model/vector_2d.h"
#include "common/periodic_clock.h"
#include "server/events/overloaded.h"

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

void Game::handle_use_weapon(const uint8_t& player_id) {
    //if (this->state != GameState::Playing) return; TODAVÍA NO CAMBIA EL ESTADO EL GAME
    auto it = players.find(player_id);
    if (it == players.end()) return;
    gamelogic.start_using_weapon(it->second, current_round);
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
    //if (this->state != GameState::Playing) return; TODAVÍA NO CAMBIA EL ESTADO EL GAME

    auto it = players.find(player_id);
    if (it == players.end()) return;
    gamelogic.buy_weapon(it->second, event.get_weapon_id(), current_round);
}


void Game::handle_start_game() {
    if (state != GameState::WaitingStart) return;

    clear_game_queue();  

    current_round = Round(180);
    state = GameState::Playing;
}

void Game::handle_leave_game(const uint8_t& player_id) {
    //Ojo ver estado de partida
    std::lock_guard<std::mutex> lock(mutex);
    auto it = players.find(player_id);
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

// solo te deja uno
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

void Game::handle_pick_role(const uint8_t player_id, const PickRoleEvent& event) {
    auto it = players.find(player_id);
    if (it != players.end()) {
        it->second.set_role_id(event.get_role_id());
    }
}

void Game::tick(uint16_t frames_to_process) {
    // compenso lo perdido (si hay)
    if(frames_to_process > 1) {
        uint16_t lost_frames = frames_to_process - 1;
        movement_system.process_movements(players, lost_frames);
        current_round.update(lost_frames);

        if (current_round.has_ended()) {
            clear_game_queue();
            broadcast_game_state();
            return;  // nuevo round    
        }
    }

    // ejecuto el tick actual
    std::pair<uint8_t, GameEventVariant> event_info;
    try {
        while (game_queue.try_pop(event_info)) {
            uint8_t player_id = event_info.first;
            GameEventVariant event = event_info.second;
            handle(player_id, event);
        }
    } catch (const ClosedQueue&) {
        // La cola está cerrada, no hay problema
    }

    movement_system.process_movements(players, 1);
    current_round.update(1);

    gamelogic.process_shooting(players, current_round);
            
    if (current_round.has_ended()) {
        clear_game_queue();
        broadcast_game_state();
        return;  // nuevo round    
    }

    broadcast_game_state();
}

void Game::broadcast_game_state() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<DTO::PlayerDTO> player_dtos;
    for (const auto& [id, player]: players) {
        player_dtos.push_back(player.to_dto());
    }

    uint16_t round_seconds_left = current_round.get_ticks_remaining() / GAME_FPS;

    DTO::GameStateDTO game_snapshot(true, player_dtos, current_round.has_ended(), round_seconds_left);

    for (auto& [id, queue]: client_queues) {
        try {
            queue->push(game_snapshot);
        } catch (const ClosedQueue&) {}
    }
}

//ojo que informo error ahora si la partida ya empezó o terminó
uint8_t Game::add_player(const std::string& username, ClientQueue& client_queue) {
    // if(state == GameState::Playing || state == GameState::Finished){
    //     return -1;
    // }
    std::lock_guard<std::mutex> lock(mutex);
    const uint8_t new_id = next_player_id++;
    players.emplace(new_id, FullPlayer(new_id, username));
    client_queues[new_id] = &client_queue;

    if (state == GameState::WaitingPlayers && players.size() >= min_players_to_start) {
        state = GameState::WaitingStart;
    }

    return new_id;
}

void Game::clear_game_queue() {
    std::pair<uint8_t, GameEventVariant> event_info;
    while(game_queue.try_pop(event_info));
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

uint8_t Game::get_num_players() const { return players.size(); }

std::string Game::get_party_name() const { return party_name; }

std::string Game::get_map_name() const { return map_name; }

GameQueue& Game::get_queue() { return game_queue; }

bool Game::is_dead() const { return !is_not_finished; }

void Game::kill() { is_not_finished = false; }

void Game::run() {
    current_round = Round();
    PeriodicClock clock(GAME_FPS);

    while (is_not_finished) {
        uint16_t frames_to_process = clock.sleep_and_get_frames();
        this->tick(frames_to_process);
    }
}

Game::~Game() {
    close();
}
