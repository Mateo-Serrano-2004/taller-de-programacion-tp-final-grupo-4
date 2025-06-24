#include "sound_effect_player.h"

#include "common/definitions.h"
#include "model/game_state.h"
#include "model/rendered_player.h"

#include "tracking_sound_effect.h"

void View::SoundEffectPlayer::play_tracked_sounds(const Model::GameState& game_state) {
    for (auto& sound: game_state.sound_effects) {
        auto player = game_state.get_player_by_id(sound->get_player_id());
        if (!player) {
            sound->end();
            continue;
        }
        sound->set_player(player);
        sound->play();
    }
}

void View::SoundEffectPlayer::play_radio_message(const Model::GameState& game_state) {
    if (game_state.start_round_radio && !game_state.start_round_radio->has_ended()) {
        game_state.start_round_radio->play();
    }
}

void View::SoundEffectPlayer::play_bomb_state(const Model::GameState& game_state) {
    if (game_state.bomb_state_sound && !game_state.bomb_state_sound->has_ended()) {
        game_state.bomb_state_sound->play();
    }
}

void View::SoundEffectPlayer::play_explosion(const Model::GameState& game_state) {
    if (game_state.bomb_explosion_sound && !game_state.bomb_explosion_sound->has_ended()) {
        game_state.bomb_explosion_sound->fix(game_state.camera);
        if (game_state.bomb_position.has_value())
            game_state.bomb_explosion_sound->set_position(game_state.bomb_position.value());
        game_state.bomb_explosion_sound->play();
    }
}

void View::SoundEffectPlayer::play_winning_sound(const Model::GameState& game_state) {
    if (game_state.winner_sound && !game_state.winner_sound->has_ended()) {
        game_state.winner_sound->play();
    }
}

void View::SoundEffectPlayer::play(const Model::GameState& game_state) {
    play_tracked_sounds(game_state);
    play_explosion(game_state);
    play_radio_message(game_state);
    play_bomb_state(game_state);
}
