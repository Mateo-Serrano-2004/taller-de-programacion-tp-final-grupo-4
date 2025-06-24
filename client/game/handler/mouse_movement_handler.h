#ifndef CLIENT_GAME_HANDLER_MOUSE_MOVEMENT_HANDLER_H
#define CLIENT_GAME_HANDLER_MOUSE_MOVEMENT_HANDLER_H

#include "common/definitions.h"

#include "game_handler.h"

namespace SDL2pp {
class Renderer;
};

namespace Controller {
class GameController;
class MouseMovementHandler {
private:
    Weak<GameController> controller;
    Shared<SDL2pp::Renderer> renderer;

public:
    explicit MouseMovementHandler(Weak<GameController> controller);

    void notify_current_rotation();

    ~MouseMovementHandler() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_MOUSE_MOVEMENT_HANDLER_H
