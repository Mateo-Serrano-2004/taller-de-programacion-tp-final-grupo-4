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
#include "model/full_player.h"
#include "server/events/events.h"

#include "movement_system.h" 
#include "round.h"
#include "game_logic.h"

using GameQueue = Queue<std::pair<uint8_t, GameEventVariant>>;
using ClientQueue = Queue<DTO::GameStateDTO>;

enum class GameState {
    WaitingStart,
    Playing,
    Finished
};

class Game: public Thread {
private:
    static constexpr int GAME_FPS = 60;
    static constexpr uint8_t MAX_ROUNDS = 10;
    uint8_t next_player_id = 0;
    std::string party_name;
    std::string map_name;
    GameQueue game_queue;

    std::map<uint8_t, FullPlayer> players;
    std::map<uint8_t, ClientQueue*> client_queues;

    std::vector<uint8_t> dropped_weapons;
    uint8_t max_players = 10;
    uint8_t min_players_to_start = 2;
    bool is_not_finished = true;
    Round current_round;
    MovementSystem movement_system;
    GameState state = GameState::WaitingStart;
    GameLogic gamelogic;
    uint8_t ct_rounds_won = 0;
    uint8_t tt_rounds_won = 0;
    uint8_t rounds_played = 0;

    void tick(uint16_t frames_to_process);  // agregar current_tick
    void broadcast_game_state();

    void handle(uint8_t player_id, const GameEventVariant& event);
    void handle_leave_game(const uint8_t& player_id);
    void handle_use_weapon(const uint8_t& player_id);
    void handle_stop_using_weapon(const uint8_t& player_id);
    void handle_movement(const uint8_t& player_id, const MovementEvent& event);
    void handle_stop_movement(const uint8_t& player_id, const StopMovementEvent& event);
    void handle_rotation(const uint8_t& player_id, const RotationEvent& event);
    void handle_pick_role(const uint8_t player_id, const PickRoleEvent& event);
    void handle_switch_weapon(const uint8_t& player_id, const SwitchWeaponEvent& event);
    void handle_buy_weapon(const uint8_t& player_id, const BuyEvent& event);
    void handle_start_game();
    void clear_game_queue();
    void start_new_round();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    Game(const std::string& party_name, const std::string& map_name):
            party_name(party_name), map_name(map_name), current_round(Round::create_warmup_round()) {
        start();
    }

    uint8_t get_num_players() const;
    std::string get_party_name() const;
    std::string get_map_name() const;
    GameQueue& get_queue();
    uint8_t add_player(const std::string& username, ClientQueue& client_queue, Model::TeamID team_id, Model::RoleID role_id);

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