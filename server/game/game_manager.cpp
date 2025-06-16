#include "game_manager.h"

#include <string>
#include <mutex>
#include <algorithm>

#include "common/team.h"

#include "server/exception/invalid_game_exception.h"

void GameManager::clear_games() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, game]: games) {
        game.reset();
    }
    games.clear();
}

void GameManager::reap_games() {
    for (auto& [id, game]: games) {
        if (game && game->is_dead()) {
            game.reset();
        }
    }
    for (auto it = games.begin(); it != games.end(); it++) {
        if (!(it->second)) {
            it = games.erase(it);
        }
    }
}

uint8_t GameManager::create_game(const std::string& party_name, const std::string& map_name,
                                 const std::string& username,
                                 Queue<DTO::GameStateDTO>& client_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    short_id_t game_id = static_cast<short_id_t>(games.size());
    games[game_id] = std::move(std::make_unique<Game>(party_name, map_name));
    games[game_id]->add_player(
        username, client_queue, 0, Model::TeamID::CT, Model::RoleID::NO_ROLE
    );
    return game_id;
}

uint8_t GameManager::join_game(const uint8_t& game_id, const std::string& username,
                               Queue<DTO::GameStateDTO>& client_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it == games.end()) throw InvalidGameException("Invalid game id");
    short_id_t player_id = it->second->get_number_of_players();
    Model::TeamID next_team_to_join = (Model::TeamID) (player_id % 2);
    it->second->add_player(username, client_queue, player_id, next_team_to_join, Model::RoleID::NO_ROLE);
    return player_id;
}

GameQueue* GameManager::get_game_queue(const uint8_t& game_id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it == games.end())
        return nullptr;
    return &it->second->get_queue();
}

std::vector<GameInfoDTO> GameManager::get_games() {
    std::lock_guard<std::mutex> lock(mtx);
    reap_games();
    std::vector<GameInfoDTO> games_info;
    for (const auto& game: games) {
        GameInfoDTO game_info = {game.first, game.second->get_party_name(),
                                 game.second->get_number_of_players(), game.second->get_map_name()};
        games_info.push_back(game_info);
    }
    return games_info;
}

std::vector<std::string> GameManager::get_name_maps() {
    return {
        "de_dust2",
        "de_mirage",
        "de_inferno",
        "de_nuke",
        "de_overpass",
        "de_train"
    };
}

std::string GameManager::get_game_map(const uint8_t& game_id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it == games.end()) throw InvalidGameException("Invalid game id");
    return it->second->get_map_name();
}

GameManager::~GameManager() {
    clear_games();
}
