#ifndef CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace Controller {
class EventHandlerStrategy {
public:
    EventHandlerStrategy() = default;

    virtual void handle(Shared<SDL_Event> event) = 0;

    virtual ~EventHandlerStrategy() = default;
};
};

#endif // CLIENT_GAME_HANDLER_EVENT_HANDLER_STRATEGY_H
