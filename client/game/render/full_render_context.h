#ifndef CLIENT_GAME_RENDER_FULL_RENDER_CONTEXT_H
#define CLIENT_GAME_RENDER_FULL_RENDER_CONTEXT_H

#include <cstdint>
#include <map>
#include <list>

#include "common/definitions.h"

#include "render_context.h"
#include "camera.h"

namespace SDL2pp {
class Texture;
}

namespace View {
class RenderedPlayer;
class MuzzleFireAnimation;
};

namespace Model {
struct FullRenderContext: public RenderContext {
public:
    std::map<short_id_t, Shared<View::RenderedPlayer>> players;
    std::list<Shared<View::MuzzleFireAnimation>> fires;
    Shared<SDL2pp::Texture> map;
    View::Camera camera;

    FullRenderContext(
        uint16_t time_left,
        Shared<View::RenderedPlayer> ref_player,
        const std::map<short_id_t, Shared<View::RenderedPlayer>>& players,
        const std::list<Shared<View::MuzzleFireAnimation>> fires,
        Shared<SDL2pp::Texture> map,
        const View::Camera& camera
    );

    ~FullRenderContext() override = default;
};
};

#endif // CLIENT_GAME_RENDER_FULL_RENDER_CONTEXT_H
