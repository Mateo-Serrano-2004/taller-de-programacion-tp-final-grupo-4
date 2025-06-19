#include "game_state.h"

#include <map>
#include <utility>

#include <SDL2pp/Texture.hh>

#include "model/rendered_player.h"

#include "animation/muzzle_fire_animation.h"

Model::GameState::GameState(): time_left(0) {}

Shared<View::RenderedPlayer> Model::GameState::get_player_by_id(Maybe<short_id_t> id) {
    if (!id.has_value())
        return nullptr;

    auto it = players.find(id.value());
    if (it == players.end())
        return nullptr;
    return it->second;
}
