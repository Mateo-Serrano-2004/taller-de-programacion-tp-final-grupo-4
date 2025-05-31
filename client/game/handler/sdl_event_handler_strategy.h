#ifndef CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "event/event.h"

namespace Controller {
class SDLEventHandlerStrategy {
protected:
    SharedQueue<SDL_Event> incoming_events_queue;
    SharedQueue<Model::Event>* dispatched_events_queue;

public:
    SDLEventHandlerStrategy(
        SharedQueue<Model::Event>* dispatched_events_queue
    );

    SharedQueue<SDL_Event>* get_communication_queue();
    virtual Shared<SDLEventHandlerStrategy> handle(Shared<SDL_Event> event) = 0;

    virtual ~SDLEventHandlerStrategy() = default;
};
};

#endif // CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_STRATEGY_H
