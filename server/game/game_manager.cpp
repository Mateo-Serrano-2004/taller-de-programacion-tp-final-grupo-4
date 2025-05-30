#include "game_manager.h"

#include <algorithm>

#include <bits/algorithmfwd.h>

uint8_t GameManager::create_game(const std::string& party_name, const std::string& map_name,
                                 const std::string& username,
                                 Queue<DTO::GameStateDTO>& client_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    games[game_counter] = std::move(std::make_unique<Game>(party_name, map_name));
    games[game_counter]->add_player(username, client_queue);
    return game_counter++;
}

uint8_t GameManager::join_game(const uint8_t& game_id, const std::string& username,
                               Queue<DTO::GameStateDTO>& client_queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it == games.end())
        return -1;
    return it->second->add_player(username, client_queue);
}

GameQueue* GameManager::get_game_queue(const uint8_t& game_id) {
    auto it = games.find(game_id);
    if (it == games.end())
        return nullptr;
    return &it->second->get_queue();
}

std::vector<GameInfoDTO> GameManager::get_games() {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<GameInfoDTO> games_info;
    for (const auto& game: games) {
        GameInfoDTO game_info = {game.first, game.second->get_party_name(),
                                 game.second->get_num_players(), game.second->get_map_name()};
        games_info.push_back(game_info);
    }
    games_info.push_back(GameInfoDTO(0, "Partida 1", 15, "de_dust2"));
    games_info.push_back(GameInfoDTO(1, "Partida 2", 0, "de_mirage"));
    games_info.push_back(GameInfoDTO(2, "Partida de prueba", 2, "de_inferno"));
    games_info.push_back(GameInfoDTO(3, "Partida de prueba de nombre largo", 0, "de_nuke"));
    games_info.push_back(GameInfoDTO(4, "Partida 3", 0, "de_overpass"));
    games_info.push_back(GameInfoDTO(5, "Partida 4", 3, "de_train"));
    return games_info;
}

std::vector<std::string> GameManager::get_name_maps() {
    std::vector<std::string> maps = {"de_dust2", "de_mirage",   "de_inferno",
                                     "de_nuke",  "de_overpass", "de_train"};
    return maps;
}

std::string GameManager::get_game_map(const uint8_t& game_id) {
    auto it = games.find(game_id);
    if (it == games.end())
        throw std::runtime_error("Game not found");
    return it->second->get_map_name();
}
