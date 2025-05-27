#include "game_state.h"

#include <utility>

std::vector<Model::Player>& Model::GameState::get_players() {
    std::lock_guard<std::mutex> lock(mutex);
    return players;
}

Model::Player& Model::GameState::get_reference_player() {
    std::lock_guard<std::mutex> lock(mutex);
    return players[reference_player_index];
}

void Model::GameState::register_player(Player&& player) {
    std::lock_guard<std::mutex> lock(mutex);
    players.emplace_back(std::move(player));
}
