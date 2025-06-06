#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/queue.h"
#include "server/events/events.h"

#include "game.h"

using GameMap = std::map<uint8_t, std::unique_ptr<Game>>;

class GameManager {
private:
    std::mutex mtx;
    GameMap games;
    std::string game_config_path;
    uint8_t game_counter = 0;
    
    void reap_games();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    explicit GameManager(const std::string& game_config_path): game_config_path(game_config_path) {}

    uint8_t create_game(const std::string& party_name, const std::string& map_name,
                        const std::string& username, Queue<DTO::GameStateDTO>& client_queue);
    uint8_t join_game(const uint8_t& game_id, const std::string& username,
                      Queue<DTO::GameStateDTO>& client_queue);

    GameQueue* get_game_queue(const uint8_t& game_id);
    std::vector<GameInfoDTO> get_games();
    std::vector<std::string> get_name_maps();

    void clear_games();
    std::string get_game_map(const uint8_t& game_id);

    GameManager(GameManager&&) = default;
    GameManager& operator=(GameManager&&) = default;

    ~GameManager() {
        clear_games();
    }
};

#endif  // GAME_MANAGER_H
