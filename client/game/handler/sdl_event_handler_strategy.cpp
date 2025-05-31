#include "sdl_event_handler_strategy.h"

#include <SDL2/SDL.h>

Controller::SDLEventHandlerStrategy::SDLEventHandlerStrategy(
        SharedQueue<Model::Event>* dispatched_events_queue
    ) : dispatched_events_queue(dispatched_events_queue) {};

SharedQueue<SDL_Event>* Controller::SDLEventHandlerStrategy::get_communication_queue() {
    return &incoming_events_queue;
}
