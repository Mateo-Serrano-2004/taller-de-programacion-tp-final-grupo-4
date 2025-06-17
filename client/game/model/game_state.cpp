#include "game_state.h"

#include <map>
#include <utility>

#include "model/rendered_player.h"

Model::GameState::GameState(): time_left(0) {}

std::map<short_id_t, Shared<View::RenderedPlayer>>& Model::GameState::get_players() {
    return players;
}

Shared<View::RenderedPlayer> Model::GameState::get_player_by_id(Maybe<short_id_t> id) {
    if (!id.has_value()) return nullptr;

    auto it = players.find(id.value());
    if (it == players.end()) return nullptr;
    return it->second;
}

void Model::GameState::register_player(Shared<View::RenderedPlayer> player) {
    players.insert({player->get_id(), player});
}

void Model::GameState::set_time_left(uint16_t new_time_left) {
    time_left = new_time_left;
}

uint16_t Model::GameState::get_time_left() const { return time_left; }
