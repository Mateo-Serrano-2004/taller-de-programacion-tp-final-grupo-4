#ifndef CLIENT_GAME_HANDLER_GAME_HANDLER_H
#define CLIENT_GAME_HANDLER_GAME_HANDLER_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace Controller {
class GameController;

class GameHandler {
protected:
    Weak<GameController> controller;

public:
    explicit GameHandler(Weak<GameController> controller);

    virtual void handle(const SDL_Event& event) = 0;
    virtual bool can_handle(const SDL_Event& event) = 0;

    virtual ~GameHandler() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_GAME_HANDLER_H
