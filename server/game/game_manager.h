#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "common/DTO/dto_variant.h"
#include "common/definitions.h"
#include "common/queue.h"
#include "server/events/events.h"
#include "server/parser/types.h"
#include "server/parser/yaml_addresser.h"
#include "server/parser/yaml_parser.h"

#include "game.h"

using GameMap = std::map<uint8_t, Unique<Game>>;

class GameManager {
private:
    std::mutex mtx;
    GameMap games;
    YamlAddresser yamlAddresser;
    YamlParser yamlParser;
    std::vector<std::string> maps_names;

    void reap_games();
    void clear_games();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    GameManager(const std::string& config_file, const std::vector<std::string>& maps_names);

    GameQueue* create_game(const std::string& party_name, const std::string& map_name,
                           const MapMatrix& map_matrix, const std::string& username,
                           Queue<DTO::DTOVariant>& client_queue);
    std::pair<short_id_t, GameQueue*> join_game(const uint8_t& game_id, const std::string& username,
                                                Queue<DTO::DTOVariant>& client_queue);

    uint8_t get_number_of_games();
    std::vector<DTO::GameInfoDTO> get_games();
    std::vector<std::string> get_name_maps();
    std::string get_game_map(const uint8_t& game_id);
    std::pair<DTO::MapDTO, MapMatrix> get_map(const std::string& map_name);

    GameManager(GameManager&&) = default;
    GameManager& operator=(GameManager&&) = default;

    ~GameManager();
};

#endif  // GAME_MANAGER_H
