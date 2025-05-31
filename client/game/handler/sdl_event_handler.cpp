#include "sdl_event_handler.h"

#include <memory>

#include "common/definitions.h"

#include "event/event.h"
#include "event/quit_event.h"
#include "event/movement_event.h"
#include "exception/closed_window.h"

void Controller::SDLEventHandler::handle_quit_event() {
    Shared<Model::QuitEvent> quit_event = make_shared<Model::QuitEvent>();
    try {
        processor_event_queue->push(quit_event);
        processor_event_queue->close();
        handler_strategy_queue->close();
    } catch (ClosedQueue& error) {
        throw App::ClosedWindowException("End of queue communication");
    }
}

Controller::SDLEventHandler::SDLEventHandler(
    SharedQueue<Model::Event>* queue,
    Shared<Controller::SDLEventHandlerStrategy> strategy
): processor_event_queue(queue),
   handler_strategy(strategy),
   handler_strategy_queue(strategy->get_communication_queue()) {
    start();
}

void Controller::SDLEventHandler::handle() {
    while (SDL_PollEvent(&placeholder)) {
        if (placeholder.type == SDL_QUIT) {
            handle_quit_event();
        } else {
            handler_strategy_queue->push(make_shared<SDL_Event>(placeholder));
        }
    }
}

void Controller::SDLEventHandler::run() {
    bool running = true;
    while (running) {
        try {
            auto event = handler_strategy_queue->pop();
            auto new_strategy = handler_strategy->handle(event);
            if (new_strategy) {
                handler_strategy = new_strategy;
            }
        } catch (...) {
            running = false;
        }
    }
}

Controller::SDLEventHandler::~SDLEventHandler() {
    stop();
    join();
}
