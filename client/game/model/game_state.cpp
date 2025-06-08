#include "game_state.h"

#include <map>
#include <utility>

Model::GameState::GameState(): time_left(0) {}

std::map<short_id_t, Model::Player>& Model::GameState::get_players() { return players; }

Model::Player& Model::GameState::get_player_by_id(short_id_t id) {
    return players.at(id);
}

void Model::GameState::register_player(Model::Player&& player) {
    players.emplace(player.get_id(), std::move(player));
}

void Model::GameState::set_time_left(uint16_t new_time_left) {
    time_left = new_time_left;
}

uint16_t Model::GameState::get_time_left() const { return time_left; }
