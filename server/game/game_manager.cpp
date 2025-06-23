#include "game_manager.h"

#include <algorithm>
#include <mutex>
#include <string>

#include "common/team.h"
#include "server/exception/invalid_game_exception.h"

GameManager::GameManager(const std::string& config_file,
                         const std::vector<std::string>& maps_names):
        yamlAddresser(),
        yamlParser(yamlAddresser.get_config_path(config_file)),
        maps_names(maps_names) {}

void GameManager::clear_games() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, game]: games) {
        game.reset();
    }
    games.clear();
}

void GameManager::reap_games() {
    for (auto it = games.begin(); it != games.end();) {
        if (it->second && it->second->is_dead()) {
            it->second.reset();
            it = games.erase(it);
        } else {
            ++it;
        }
    }
}

GameQueue* GameManager::create_game(const std::string& party_name, const std::string& map_name,
                                    const MapMatrix& map_matrix, const std::string& username,
                                    Queue<DTO::DTOVariant>& client_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    reap_games();
    short_id_t game_id = static_cast<short_id_t>(games.size());
    games[game_id] = std::move(std::make_unique<Game>(party_name, map_name, map_matrix));
    games[game_id]->add_player(username, client_queue, 0, Model::TeamID::CT,
                               Model::RoleID::NO_ROLE);
    return &games[game_id]->get_queue();
}

std::pair<short_id_t, GameQueue*> GameManager::join_game(const uint8_t& game_id,
                                                         const std::string& username,
                                                         Queue<DTO::DTOVariant>& client_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    reap_games();
    auto it = games.find(game_id);
    if (it == games.end())
        throw InvalidGameException("Invalid game id");
    auto pair = std::make_pair<short_id_t, GameQueue*>(it->second->get_number_of_players(),
                                                       &it->second->get_queue());
    Model::TeamID next_team_to_join = (Model::TeamID)(pair.first % 2);
    it->second->add_player(username, client_queue, pair.first, next_team_to_join,
                           Model::RoleID::NO_ROLE);
    return pair;
}

std::vector<DTO::GameInfoDTO> GameManager::get_games() {
    std::lock_guard<std::mutex> lock(mtx);
    reap_games();
    std::vector<DTO::GameInfoDTO> games_info;
    for (const auto& game: games) {
        if (!game.second->is_valid())
            continue;
        DTO::GameInfoDTO game_info = {game.first, game.second->get_party_name(),
                                      game.second->get_number_of_players(),
                                      game.second->get_map_name()};
        games_info.push_back(game_info);
    }
    return games_info;
}

std::vector<std::string> GameManager::get_name_maps() { return maps_names; }

std::string GameManager::get_game_map(const uint8_t& game_id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it == games.end())
        throw InvalidGameException("Invalid game id");
    return it->second->get_map_name();
}

std::pair<DTO::MapDTO, MapMatrix> GameManager::get_map(const std::string& map_name) {
    std::lock_guard<std::mutex> lock(mtx);
    yamlParser.parseMapYaml(yamlAddresser.get_map_path(map_name));
    return std::make_pair(DTO::MapDTO(yamlParser.getTileMatrix()), yamlParser.getTypeMatrix());
}

GameManager::~GameManager() { clear_games(); }
