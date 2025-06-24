#include "animation_renderer.h"

#include <cstdint>

#include "animation/bomb_explosion_animation.h"
#include "animation/muzzle_fire_animation.h"
#include "animation/progress_bar_animation.h"
#include "animation/winner_team_message_animation.h"
#include "model/game_state.h"
#include "model/rendered_player.h"

void View::AnimationRenderer::render_muzzle_fires(const Model::GameState& game_state,
                                                  uint8_t frames) {
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

void View::AnimationRenderer::render_winner_message(const Model::GameState& game_state,
                                                    uint8_t frames) {
    if (game_state.winner_message) {
        game_state.winner_message->step(frames);
    }
}

void View::AnimationRenderer::render_progress_bar(const Model::GameState& game_state) {
    if (game_state.progress_bar) {
        if (game_state.defusing_progress) {
            game_state.progress_bar->progress(game_state.defusing_progress);
        } else {
            auto ref_player = game_state.get_reference_player();
            game_state.progress_bar->progress(ref_player->get_planting_progress());
        }
    }
}

void View::AnimationRenderer::render_explosion(const Model::GameState& game_state, uint8_t frames) {
    if (game_state.bomb_explosion) {
        game_state.bomb_explosion->fix(game_state.camera);
        game_state.bomb_explosion->step(frames);
    }
}
