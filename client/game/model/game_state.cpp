#include "game_state.h"

#include <algorithm>
#include <map>
#include <utility>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Texture.hh>

#include "animation/bomb_explosion_animation.h"
#include "animation/muzzle_fire_animation.h"
#include "animation/progress_bar_animation.h"
#include "animation/winner_team_message_animation.h"
#include "common/DTO/drop_weapon_dto.h"
#include "model/rendered_player.h"
#include "sound/distanced_sound_effect.h"
#include "sound/sound_effect.h"
#include "sound/tracking_sound_effect.h"

Model::GameState::GameState():
        reference_player_id(std::nullopt),
        bomb_defused(false),
        bomb_planted(false),
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

Shared<View::RenderedPlayer> Model::GameState::get_any_player_by_team(Model::TeamID team) const {
    auto it = std::find_if(players.begin(), players.end(), [&team](const auto& player) {
        return (player.second->get_team() == team && player.second->get_health() > 0);
    });
    if (it == players.end())
        return nullptr;
    return it->second;
}

Shared<View::RenderedPlayer> Model::GameState::get_any_player_alive() const {
    auto it = std::find_if(players.begin(), players.end(),
                           [](const auto& player) { return player.second->get_health() > 0; });
    if (it == players.end())
        return nullptr;
    return it->second;
}

Shared<View::RenderedPlayer> Model::GameState::get_any_player_alive_by_team(
        Model::TeamID team) const {
    auto player = get_any_player_by_team(team);
    if (player)
        return player;

    return get_any_player_alive();
}
