#include "game_state.h"

#include <map>
#include <utility>

std::map<short_id_t, Model::Player>& Model::GameState::get_players() {
    return players;
}

void Model::GameState::register_player(Model::Player&& player) {
    players.emplace(player.get_id(), std::move(player));
}
