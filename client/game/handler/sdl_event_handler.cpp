#include "sdl_event_handler.h"

#include <atomic>
#include <iostream>

#include "common/event/event.h"
#include "common/event/quit_event.h"

#include "exception/closed_window.h"

Controller::SDLEventHandler::SDLEventHandler(
    SharedQueue<Model::Event>& queue
) : event_queue(queue) {}

void Controller::SDLEventHandler::handle() {
    while (SDL_PollEvent(&placeholder)) {
        if (placeholder.type == SDL_QUIT) {
            std::cout << SDL_QUIT << "\n";
            Shared<Model::QuitEvent> quit_event = make_shared<Model::QuitEvent>();
            try {
                event_queue.try_push(quit_event);
            } catch (ClosedQueue& error) {
                throw App::ClosedWindowException("Received a QUIT event");
            }
        }
    }
}
