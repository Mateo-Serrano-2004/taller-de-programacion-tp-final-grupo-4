#include "game_state.h"

#include <utility>

std::vector<Model::Player>& Model::GameState::get_players() {
    std::lock_guard<std::mutex> lock(mutex);
    return players;
}

uint8_t Model::GameState::get_reference_player_id() const {
    return reference_player_id;
}

Model::Player& Model::GameState::get_reference_player() {
    std::lock_guard<std::mutex> lock(mutex);
    return players.at(reference_player_id);
}

void Model::GameState::register_player(Player&& player) {
    std::lock_guard<std::mutex> lock(mutex);
    players.insert({ player.get_id(), std::move(player) });
}

void Model::GameState::update(Shared<GameState> new_game_state) {
    std::lock_guard<std::mutex> lock(mutex);
    players = std::move(new_game_state->players);
    reference_player_index = new_game_state->reference_player_index;
}
