#include "game_state.h"

#include <map>
#include <mutex>
#include <utility>
#include <functional>

std::map<uint8_t, Model::Player>& Model::GameState::get_players() {
    std::lock_guard<std::mutex> lock(mutex);
    return players;
}

uint8_t Model::GameState::get_reference_player_id() const { return reference_player_id; }

Model::Player& Model::GameState::get_reference_player() {
    return players.at(reference_player_id);
}

void Model::GameState::map_function_on_players(std::function<void(Player&)> func) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& [id, player] : players) {
        func(player);
    }
}

void Model::GameState::register_player(Model::Player&& player) {
    std::lock_guard<std::mutex> lock(mutex);
    players.insert({player.get_id(), std::move(player)});
}

void Model::GameState::update(Shared<Model::GameState> new_game_state) {
    std::lock_guard<std::mutex> lock(mutex);
    players = std::move(new_game_state->players);
    reference_player_id = new_game_state->reference_player_id;
}
