#include "sound_effect_player.h"

#include "common/definitions.h"
#include "model/game_state.h"
#include "model/rendered_player.h"

#include "sound_effect.h"

void View::SoundEffectPlayer::play(const Model::GameState& game_state) {
    for (auto& shot: game_state.shot_sounds) {
        auto player = game_state.get_player_by_id(shot->get_player_id());
        if (!player) {
            shot->end();
            continue;
        }
        shot->set_player(player);
        shot->play();
    }
}
