#include "sound_effect_player.h"

#include <iostream>

#include "common/definitions.h"
#include "model/game_state.h"
#include "model/rendered_player.h"

#include "tracking_sound_effect.h"

void View::SoundEffectPlayer::play(const Model::GameState& game_state) {
    for (auto& shot: game_state.sound_effects) {
        auto player = game_state.get_player_by_id(shot->get_player_id());
        if (!player) {
            shot->end();
            continue;
        }
        shot->set_player(player);
        shot->play();
    }
    if (
        game_state.bomb_explosion_sound &&
       !game_state.bomb_explosion_sound->has_ended()
    ) {
        game_state.bomb_explosion_sound->fix(game_state.camera);
        if (game_state.bomb_position.has_value())
            game_state.bomb_explosion_sound->set_position(game_state.bomb_position.value());
        game_state.bomb_explosion_sound->play();
    }
}
