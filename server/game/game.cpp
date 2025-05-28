#include "game.h"

#include <iostream>

#include "vector2d.h"
#include "server/events/overloaded.h"

void Game::run() {
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;

    const Duration RATE = std::chrono::duration_cast<Duration>(std::chrono::duration<double>(1.0 / 60.0));
    
    TimePoint t1 = Clock::now();
    int current_tick = 0;

    while (is_not_finished) {

        tick();  // falta número de tick

        TimePoint t2 = Clock::now();
        Duration rest = RATE - (t2 - t1);

        if (rest < Duration::zero()) {
            Duration behind = -rest;
            Duration lost = behind + RATE - (behind % RATE);
            t1 += lost;
            current_tick += static_cast<int>(lost / RATE);
        } else {
            std::this_thread::sleep_for(rest);
            t1 += RATE;
            current_tick++;
        }
    }
}

void Game::handle_leave_game(const uint8_t& player_id){
    auto it = players.find(player_id);
    players.erase(it);
    auto queue_it = client_queues.find(player_id);
    client_queues.erase(queue_it);
}

void Game::handle_movement(const uint8_t& player_id, const MovementEvent& event){
    auto it = players.find(player_id);
    if (it != players.end() && it->second.alive()) {
        it->second.set_direction(Vector2D((event.get_x()),(event.get_y())));
    }
}

void Game::tick() { //agregar current_tick
    std::pair<uint8_t, GameEventVariant> event_info;
    if (game_queue.try_pop(event_info)) {
        uint8_t player_id = event_info.first;
        GameEventVariant event = event_info.second;
        std::visit(overloaded{
            [player_id, this](const MovementEvent& e) { handle_movement(player_id, e); },
            [player_id, this](const LeaveGameEvent&) { handle_leave_game(player_id); },
            [this](const RotationEvent&) {},
            [this](const DropWeaponEvent&) {},
            [this](const UseWeaponEvent&) {},
            [this](const DefuseBombEvent&) {},
            [this](const SwitchWeaponEvent&) {},
            [this](const ReloadWeaponEvent&) {},
            [this](const BuyEvent&) {},
            [this](const BuyAmmoEvent&) {},
            [this](const QuitEvent&) {}
        }, event);
    }

    // aca deberia loopear por la cantidad de ticks perdidos? teniendo registro aca mismo?
    for (auto& [id, player] : players) {
        player.update_position();
    }

    broadcast_game_state();
}

void Game::broadcast_game_state() {
    std::vector<PlayerDTO> player_dtos;
    for (const auto& [id, player] : players) {
        player_dtos.push_back(player.to_dto());
    }

    MatchCreator game_snapshot(
        true,
        0, 0, 0, 0,
        player_dtos,
        {},
        0, 0, 0,
        0
    );

    for (auto& [id, queue] : client_queues) {
        queue->push(game_snapshot);
    }
}

uint8_t Game::add_player(const std::string& username, ClientQueue& client_queue) {
    uint8_t new_id = next_player_id++;
    players.emplace(new_id, Player(new_id, username, Team::CT, 800));  //ojo bando
    client_queues[new_id] = &client_queue;
    return new_id;
}

uint8_t Game::get_num_players() const {
    return players.size();
}

std::string Game::get_party_name() const {
    return party_name;
}

std::string Game::get_map_name() const {
    return map_name;
}

GameQueue& Game::get_queue() { 
    return game_queue; 
}

void Game::stop() {
    is_not_finished = false;
}