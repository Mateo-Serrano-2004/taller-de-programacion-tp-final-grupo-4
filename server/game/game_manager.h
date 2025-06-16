#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "common/definitions.h"
#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/queue.h"

#include "server/events/events.h"

#include "game.h"

using GameMap = std::map<uint8_t, Unique<Game>>;

class GameManager {
private:
    std::mutex mtx;
    GameMap games;

    void reap_games();
    void clear_games();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    GameManager() = default;

    uint8_t create_game(const std::string& party_name, const std::string& map_name,
                        const std::string& username, Queue<DTO::GameStateDTO>& client_queue);
    uint8_t join_game(const uint8_t& game_id, const std::string& username,
                      Queue<DTO::GameStateDTO>& client_queue);

    GameQueue* get_game_queue(const uint8_t& game_id);
    uint8_t get_number_of_games();
    std::vector<GameInfoDTO> get_games();
    std::vector<std::string> get_name_maps();
    std::string get_game_map(const uint8_t& game_id);

    GameManager(GameManager&&) = default;
    GameManager& operator=(GameManager&&) = default;

    ~GameManager();
};

#endif  // GAME_MANAGER_H
