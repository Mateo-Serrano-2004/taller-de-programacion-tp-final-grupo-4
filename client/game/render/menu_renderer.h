#ifndef CLIENT_GAME_RENDER_MENU_RENDERER_H
#define CLIENT_GAME_RENDER_MENU_RENDERER_H

#include "common/definitions.h"

namespace SDL2pp {
class Window;
class Renderer;
};

namespace Model {
class TextureStorage;
};

namespace Controller {
class GameController;
};

namespace Controller {
class GameController;
};

namespace View {
class MenuRenderer {
protected:
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::TextureStorage> texture_storage;

public:
    MenuRenderer(Weak<Controller::GameController> controller);

    void render_menu();

    ~MenuRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_MENU_RENDERER_H
