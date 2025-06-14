#ifndef GAME_H
#define GAME_H

#include <mutex>
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
#include "common/game_state.h"
#include "model/full_player.h"
#include "server/events/events.h"

#include "movement_system.h" 
#include "round.h"
#include "game_logic.h"

using GameQueue = Queue<std::pair<uint8_t, GameEventVariant>>;
using ClientQueue = Queue<DTO::GameStateDTO>;

class Game: public Thread {
private:
    std::mutex mutex;

    // Pre-initialized attributes
    const int GAME_FPS = 60;
    const uint8_t MAX_ROUNDS = 10;
    const uint8_t max_players = 10;
    const uint8_t min_players_to_start = 2;
    GameState state = GameState::WaitingStart;
    bool is_not_finished = true;
    uint8_t ct_rounds_won = 0;
    uint8_t tt_rounds_won = 0;
    uint8_t rounds_played = 0;
    uint8_t next_player_id = 0;

    // Default constructible attributes
    GameQueue game_queue;
    std::map<uint8_t, FullPlayer> players;
    std::map<uint8_t, ClientQueue*> client_queues;
    std::vector<uint8_t> dropped_weapons;
    MovementSystem movement_system;
    GameLogic gamelogic;
    Round round;

    // Non-default constructible attributes
    std::string party_name;
    std::string map_name;

    void handle_leave_game(const uint8_t& player_id);
    void handle_use_weapon(const uint8_t& player_id);
    void handle_stop_using_weapon(const uint8_t& player_id);
    void handle_movement(const uint8_t& player_id, const MovementEvent& event);
    void handle_stop_movement(const uint8_t& player_id, const StopMovementEvent& event);
    void handle_rotation(const uint8_t& player_id, const RotationEvent& event);
    void handle_pick_role(const uint8_t player_id, const PickRoleEvent& event);
    void handle_switch_weapon(const uint8_t& player_id, const SwitchWeaponEvent& event);
    void handle_buy_weapon(const uint8_t& player_id, const BuyEvent& event);

    void handle(uint8_t player_id, const GameEventVariant& event);

    void clear_game_queue();
    void start_new_round();

    void update_players_that_won();
    void process_frames(uint16_t frames_to_process = 1);
    void update_game_with_events();
    void broadcast_game_state();
    void tick(uint16_t frames_to_process);  // TODO: Add current_tick

    void close();

    // Threads cannot be either copied or moved
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

public:
    Game(const std::string& party_name, const std::string& map_name);

    uint8_t get_number_of_players() const;
    std::string get_party_name() const;
    std::string get_map_name() const;
    GameQueue& get_queue();

    bool is_dead() const;

    uint8_t add_player(const std::string& username, ClientQueue& client_queue, Model::TeamID team_id, Model::RoleID role_id);

    void kill();
    void run() override;

    ~Game() override;
};

#endif  // GAME_H