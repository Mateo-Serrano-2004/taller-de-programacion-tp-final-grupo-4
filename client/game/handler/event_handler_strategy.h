#ifndef CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace Controller {
class BaseController;

class EventHandlerStrategy {
protected:
    SDL_Event current_event;
    Weak<BaseController> controller;

    void handle_quit_event();

    // Empty implementation for dummy handlers
    virtual void handle_switch_context_event();

public:
    explicit EventHandlerStrategy(Weak<BaseController> controller);

    virtual void handle();
    virtual void dispatch();

    virtual ~EventHandlerStrategy() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H
