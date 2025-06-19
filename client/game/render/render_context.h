#ifndef CLIENT_GAME_RENDER_RENDER_CONTEXT_H
#define CLIENT_GAME_RENDER_RENDER_CONTEXT_H

#include <cstdint>

#include "common/definitions.h"

namespace View {
class RenderedPlayer;
};

namespace Model {
struct RenderContext {
public:
    uint16_t time_left;
    Shared<View::RenderedPlayer> ref_player;

    RenderContext(uint16_t time_left, Shared<View::RenderedPlayer> ref_player);
    virtual ~RenderContext() = default;
};
};

#endif // CLIENT_GAME_RENDER_RENDER_CONTEXT_H
