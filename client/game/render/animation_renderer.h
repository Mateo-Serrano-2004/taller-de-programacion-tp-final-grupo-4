#ifndef CLIENT_GAME_RENDER_ANIMATION_RENDERER_H
#define CLIENT_GAME_RENDER_ANIMATION_RENDERER_H

#include <cstdint>

namespace Model {
class GameState;
};

namespace View {
class AnimationRenderer {
public:
    AnimationRenderer() = default;

    void render_muzzle_fires(const Model::GameState& game_state, uint8_t frames);
    void render_winner_message(const Model::GameState& game_state, uint8_t frames);
    void render_progress_bar(const Model::GameState& game_state);
    void render_explosion(const Model::GameState& game_state, uint8_t frames);

    ~AnimationRenderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_ANIMATION_RENDERER_H
