#include "game_state.h"

#include <map>
#include <utility>

std::map<short_id_t, Model::Player>& Model::GameState::get_players() {
    return players;
}

Model::Player& Model::GameState::get_player_by_id(short_id_t id) {
    return players.at(id);
}

void Model::GameState::register_player(Model::Player&& player) {
    players.emplace(player.get_id(), std::move(player));
}
