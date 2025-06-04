#ifndef CLIENT_GAME_RENDER_MENU_RENDERER_H
#define CLIENT_GAME_RENDER_MENU_RENDERER_H

#include "common/definitions.h"

#include "renderer.h"

namespace Controller {
class GameController;
};

namespace View {
class MenuRenderer: public Renderer {
public:
    MenuRenderer(Weak<Controller::GameController> controller);

    void render() override;

    ~MenuRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_MENU_RENDERER_H
