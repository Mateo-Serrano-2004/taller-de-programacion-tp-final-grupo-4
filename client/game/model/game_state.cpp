#include "game_state.h"

#include <map>
#include <utility>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Texture.hh>

#include "animation/muzzle_fire_animation.h"
#include "animation/progress_bar_animation.h"
#include "animation/winner_team_message_animation.h"
#include "sound/sound_effect.h"
#include "model/rendered_player.h"

Model::GameState::GameState():
        reference_player_id(std::nullopt),
        bomb_position(std::nullopt),
        time_left(0),
        defusing_progress(0),
        first_team_victories(0),
        second_team_victories(0),
        round_winner(Model::TeamID::NONE),
        game_winner(Model::TeamID::NONE),
        round_state(RoundState::Warmup) {}

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
