#ifndef CLIENT_GAME_RENDER_RENDERER_H
#define CLIENT_GAME_RENDER_RENDERER_H

#include <cstdint>

#include "common/definitions.h"

namespace SDL2pp {
class Window;
class Renderer;
};  // namespace SDL2pp

namespace Model {
class AssetManager;
struct GameState;
};  // namespace Model

namespace Controller {
class BaseController;
};

namespace View {
class Renderer {
protected:
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::AssetManager> asset_manager;

public:
    explicit Renderer(Weak<Controller::BaseController> controller);

    virtual void render(const Model::GameState& game_state, uint8_t frames) = 0;

    virtual ~Renderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_RENDERER_H
