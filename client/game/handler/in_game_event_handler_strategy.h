#ifndef CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "sdl_event_handler_strategy.h"
#include "handler_state.h"

namespace Controller {
class InGameEventHandlerStrategy: public SDLEventHandlerStrategy {
private:
    Model::HandlerState handler_state;

    Shared<SDLEventHandlerStrategy> handle_keydown_event(Shared<SDL_Event> event);
    Shared<SDLEventHandlerStrategy> handle_keyup_event(Shared<SDL_Event> event);

public:
    InGameEventHandlerStrategy(
        SharedQueue<Model::Event>* dispatched_events_queue
    );

    Shared<SDLEventHandlerStrategy> handle(Shared<SDL_Event> event) override;

    ~InGameEventHandlerStrategy() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
