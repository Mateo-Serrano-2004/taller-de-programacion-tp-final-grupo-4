#include "client/game/sdl_controller.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include <iostream>

#include "client/game/exception/closed_window.h"

Controller::SDLController::SDLController() {
    start();
}

void Controller::SDLController::handle_event(TS<Event> event) {
    TS<SDLEvent> sdl_event = std::static_pointer_cast<SDLEvent>(event);
    const Uint32 event_type = sdl_event->type();
    switch (event_type) {
        case SDL_QUIT:
            try {
                dispatched_events_queue.close();
            } catch (...) {}
            queue.close();
            break;
        case SDL_KEYDOWN:
            std::cout << "\nA key has been pressed!";
            TS<SDLEvent> dummy_event;
            send_message(dummy_event);
            break;
    }
}

void Controller::SDLController::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        // if (placeholder.type == SDL_QUIT) {
        //     throw App::ClosedWindowException("Received a QUIT event");
        // }
        try {
            dispatched_events_queue.try_push(make_TS<SDLEvent>(placeholder));
        } catch (ClosedQueue& error) {
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }
}
