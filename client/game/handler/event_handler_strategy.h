#ifndef CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace Controller {
class BaseController;

class EventHandlerStrategy {
protected:
    SDL_Event placeholder;
    Weak<BaseController> controller;

    void handle_quit_event();
    virtual void handle_switch_context_event(Shared<SDL_Event> event) = 0;

public:
    EventHandlerStrategy(Weak<BaseController> controller);

    virtual void handle(Shared<SDL_Event> event);

    virtual ~EventHandlerStrategy() = default;
};
};

#endif // CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H
