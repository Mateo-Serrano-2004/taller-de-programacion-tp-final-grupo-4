#ifndef CLIENT_GAME_RENDER_MENU_RENDERER_H
#define CLIENT_GAME_RENDER_MENU_RENDERER_H

#include <list>

#include "common/definitions.h"

#include "renderer.h"

namespace View {
class Rendered;
};

namespace Controller {
class GameController;
};

namespace View {
class MenuRenderer: public Renderer {
protected:
    std::list<Shared<Rendered>> rendereds;

public:
    explicit MenuRenderer(Weak<Controller::GameController> controller);

    void add_to_render(Shared<Rendered> rendered);
    void render() override;

    ~MenuRenderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_MENU_RENDERER_H
