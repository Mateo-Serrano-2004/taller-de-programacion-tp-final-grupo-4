#include "event_handler_strategy.h"

#include <memory>

#include "event/quit_event.h"
#include "controller/base_controller.h"

void Controller::EventHandlerStrategy::handle_quit_event() {
    auto quit_event = make_shared<Model::QuitEvent>();
    controller.lock()->handle_event(quit_event);
}

void Controller::EventHandlerStrategy::handle(Shared<SDL_Event> event) {
    auto type = event->type;
    if (type == SDL_QUIT) handle_quit_event();
}

Controller::EventHandlerStrategy::EventHandlerStrategy(
    Weak<Controller::BaseController> controller
): controller(controller) {}
