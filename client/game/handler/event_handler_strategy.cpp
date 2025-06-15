#include "event_handler_strategy.h"

#include <memory>
#include <utility>

#include "controller/base_controller.h"

#include "event/quit_event.h"

void Controller::EventHandlerStrategy::handle_quit_event() {
    controller.lock()->push_event(make_shared<Model::QuitEvent>());
}

void Controller::EventHandlerStrategy::handle(Shared<SDL_Event> event) {
    auto type = event->type;
    if (type == SDL_QUIT) handle_quit_event();
}

Controller::EventHandlerStrategy::EventHandlerStrategy(
    Weak<Controller::BaseController> controller
): controller(controller) {}
