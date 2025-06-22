#include "animation_renderer.h"

#include <cstdint>

#include "animation/muzzle_fire_animation.h"
#include "animation/progress_bar_animation.h"
#include "animation/winner_team_message_animation.h"
#include "model/game_state.h"
#include "model/rendered_player.h"

void View::AnimationRenderer::render_muzzle_fires(const Model::GameState& game_state, uint8_t frames) {
    for (auto& animation: game_state.fires) {
        auto player = game_state.get_player_by_id(animation->get_player_id());
        if (!player) {
            animation->end();
            continue;
        }
        animation->set_player(player);
        animation->step(frames);
    }
}

void View::AnimationRenderer::render_winner_message(const Model::GameState& game_state, uint8_t frames) {
    if (game_state.winner_message) {
        game_state.winner_message->step(frames);
    }
}

void View::AnimationRenderer::render_defusing_progress(const Model::GameState& game_state) {
    if (game_state.bomb_defusing) {
        game_state.bomb_defusing->progress(game_state.defusing_progress);
    }
}
