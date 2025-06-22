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
    void render_defusing_progress(const Model::GameState& game_state);

    ~AnimationRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_ANIMATION_RENDERER_H
