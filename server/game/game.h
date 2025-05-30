#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <cmath>
#include <cstdint>
#include <map>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/queue.h"
#include "common/thread.h"
#include "model/movable_player.h"
#include "server/events/events.h"

using GameQueue = Queue<std::pair<uint8_t, GameEventVariant>>;
using ClientQueue = Queue<DTO::GameStateDTO>;

class Game: public Thread {
private:
    uint8_t next_player_id = 0;
    std::string party_name;
    std::string map_name;
    GameQueue game_queue;

    std::map<uint8_t, Model::MovablePlayer> players;
    std::map<uint8_t, ClientQueue*> client_queues;

    std::vector<uint8_t> dropped_weapons;
    uint8_t time_remaining = 0;
    uint8_t bomb_planted = 0;
    uint8_t bomb_defused = 0;
    uint8_t bomb_exploded = 0;
    uint8_t ct_rounds_won = 0;
    uint8_t t_rounds_won = 0;
    uint8_t max_players = 12;
    bool is_not_finished = true;

    void tick();  // agregar current_tick
    void broadcast_game_state();

    void handle_leave_game(const uint8_t& player_id);
    void handle_movement(const uint8_t& player_id, const MovementEvent& event);

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    Game(const std::string& party_name, const std::string& map_name):
            party_name(party_name), map_name(map_name) {
        start();
    }

    uint8_t get_num_players() const;
    std::string get_party_name() const;
    std::string get_map_name() const;
    GameQueue& get_queue();
    uint8_t add_player(const std::string& username, ClientQueue& client_queue);

    void run() override;
    bool is_dead() const;
    void kill();
    void stop() override;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    ~Game() override {
        is_not_finished = false;
        join();
    }
};

#endif  // GAME_H
