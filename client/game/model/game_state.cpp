#include "game_state.h"

#include <map>
#include <utility>

#include <SDL2pp/Texture.hh>

#include "animation/muzzle_fire_animation.h"
#include "model/rendered_player.h"

Model::GameState::GameState(): reference_player_id(std::nullopt), time_left(0) {}

Model::GameState::GameState(const GameState& other):
        players(other.players),
        fires(other.fires),
        camera(other.camera),
        map(other.map),
        reference_player_id(other.reference_player_id),
        time_left(other.time_left) {}

Shared<View::RenderedPlayer> Model::GameState::get_reference_player() const {
    return get_player_by_id(reference_player_id);
}

Shared<View::RenderedPlayer> Model::GameState::get_player_by_id(Maybe<short_id_t> id) const {
    if (!id.has_value())
        return nullptr;

    auto it = players.find(id.value());
    if (it == players.end())
        return nullptr;
    return it->second;
}
