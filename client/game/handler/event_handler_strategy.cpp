#include "event_handler_strategy.h"

#include <memory>
#include <utility>

#include <SDL2/SDL.h>

#include "controller/base_controller.h"
#include "event/quit_event.h"

void Controller::EventHandlerStrategy::handle_quit_event() {
    controller.lock()->push_event(make_shared<Model::QuitEvent>());
}

void Controller::EventHandlerStrategy::handle_switch_context_event() {}

void Controller::EventHandlerStrategy::handle() {
    auto type = current_event.type;
    if (type == SDL_QUIT)
        handle_quit_event();
}

void Controller::EventHandlerStrategy::dispatch() {
    while (SDL_PollEvent(&current_event)) {
        handle();
    }
}

Controller::EventHandlerStrategy::EventHandlerStrategy(Weak<Controller::BaseController> controller):
        controller(controller) {}
