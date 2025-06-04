#ifndef CLIENT_GAME_RENDER_RENDERER_H
#define CLIENT_GAME_RENDER_RENDERER_H

#include "common/definitions.h"

namespace SDL2pp {
class Window;
class Renderer;
};

namespace Model {
class TextureStorage;
};

namespace Controller {
class BaseController;
};

namespace View {
class Renderer {
protected:
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::TextureStorage> texture_storage;

public:
    Renderer(Weak<Controller::BaseController> controller);

    virtual void render() = 0;

    virtual ~Renderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_RENDERER_H
