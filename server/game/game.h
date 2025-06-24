#ifndef GAME_H
#define GAME_H

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "common/DTO/dto_variant.h"
#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/definitions.h"
#include "common/game_state.h"
#include "common/queue.h"
#include "common/thread.h"
#include "model/full_player.h"
#include "server/events/events.h"
#include "server/parser/types.h"

#include "game_logic.h"
#include "movement_system.h"
#include "round.h"

using GameQueue = Queue<std::pair<uint8_t, GameEventVariant>>;
using ClientQueue = Queue<DTO::DTOVariant>;

class Game: public Thread {
private:
    std::mutex mutex;

    std::vector<Physics::Vector2D> ct_spawn_positions;
    std::vector<Physics::Vector2D> tt_spawn_positions;
    std::vector<Physics::Vector2D> bomb_sites;

    const int GAME_FPS = 60;
    uint8_t max_rounds;
    uint8_t rounds_per_side;
    int round_won_money;
    int round_lost_money;
    const uint8_t max_players = 10;
    const uint8_t min_players_to_start = 2;
    GameState state = GameState::WaitingStart;
    std::atomic<bool> is_not_finished = true;
    uint8_t ct_rounds_won = 0;
    uint8_t tt_rounds_won = 0;
    uint8_t rounds_played = 0;

    GameQueue game_queue;
    std::map<short_id_t, FullPlayer> players;
    std::map<short_id_t, ClientQueue*> client_queues;
    std::vector<uint8_t> dropped_weapons;
    GameLogic gamelogic;
    Round round;

    std::string party_name;
    std::string map_name;
    MapMatrix map_matrix;
    MovementSystem movement_system;

    bool is_playing_state();
    void with_valid_player(short_id_t player_id, std::function<void(FullPlayer&)> action);

    void handle_leave_game(const uint8_t& player_id);
    void handle_use_weapon(const uint8_t& player_id);
    void handle_stop_using_weapon(const uint8_t& player_id);
    void handle_start_defusing_bomb(const uint8_t& player_id);
    void handle_stop_defusing_bomb(const uint8_t& player_id);
    void handle_reload(const uint8_t& player_id);
    void handle_movement(const uint8_t& player_id, const MovementEvent& event);
    void handle_stop_movement(const uint8_t& player_id, const StopMovementEvent& event);
    void handle_rotation(const uint8_t& player_id, const RotationEvent& event);
    void handle_pick_role(const uint8_t player_id, const PickRoleEvent& event);
    void handle_switch_weapon(const uint8_t& player_id, const SwitchWeaponEvent& event);
    void handle_buy_weapon(const uint8_t& player_id, const BuyEvent& event);
    void handle_buy_ammo(const uint8_t& player_id, const BuyAmmoEvent& event);
    void handle_drop_weapon(const uint8_t& player_id);

    void handle(uint8_t player_id, const GameEventVariant& event);

    void swap_teams();

    void clear_game_queue();
    void start_new_round();

    Physics::Vector2D get_position_for_new_player(Model::TeamID team);

    void load_map_features();

    void update_players_that_won();
    void process_frames(uint16_t frames_to_process = 1);
    void update_game_with_events();
    void broadcast_game_state();
    void tick(uint16_t frames_to_process);

    void close();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

public:
    Game(const std::string& party_name, const std::string& map_name, const MapMatrix& type_matrix);

    uint8_t get_number_of_players();
    std::string get_party_name();
    std::string get_map_name();
    GameQueue& get_queue();

    bool is_valid();
    bool is_dead();

    void add_player(const std::string& username, ClientQueue& client_queue, short_id_t player_id,
                    Model::TeamID team_id, Model::RoleID role_id);

    void kill();
    void run() override;

    ~Game() override;
};

#endif  // GAME_H
