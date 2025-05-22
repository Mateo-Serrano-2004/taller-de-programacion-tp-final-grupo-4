#include "game_state.h"

#include <utility>

std::vector<Model::Player>& Model::GameState::get_players() {
    std::lock_guard<std::mutex> lock(mutex);
    return players;
}

void Model::GameState::register_player(Player&& player) {
    std::lock_guard<std::mutex> lock(mutex);
    players.emplace_back(std::move(player));
}
