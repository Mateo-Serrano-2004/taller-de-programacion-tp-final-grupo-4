#ifndef CLIENT_GAME_ENTITY_RENDERED_H
#define CLIENT_GAME_ENTITY_RENDERED_H

#include <SDL2pp/Renderer.hh>

#include "common/definitions.h"

namespace Controller {
class BaseController;
};

namespace View {
class Rendered {
protected:
    Shared<SDL2pp::Renderer> renderer;

public:
    explicit Rendered(Weak<Controller::BaseController> controller);

    virtual void render() = 0;

    virtual ~Rendered() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_RENDERED_H
