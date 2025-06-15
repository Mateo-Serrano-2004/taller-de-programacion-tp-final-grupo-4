#include "event_handler_strategy.h"

#include <memory>
#include <utility>

#include "controller/base_controller.h"

#include "event/quit_event.h"
#include "event/window_resize_event.h"

void Controller::EventHandlerStrategy::handle_quit_event() {
    controller.lock()->push_event(make_shared<Model::QuitEvent>());
}

void Controller::EventHandlerStrategy::handle_window_resize_event() {
    controller.lock()->push_event(make_shared<Model::WindowResizeEvent>());
}

void Controller::EventHandlerStrategy::handle(Shared<SDL_Event> event) {
    auto type = event->type;
    if (type == SDL_QUIT) handle_quit_event();
    else if (type == SDL_WINDOWEVENT) {
        if (event->window.event == SDL_WINDOWEVENT_RESIZED) handle_window_resize_event();
    }
}

Controller::EventHandlerStrategy::EventHandlerStrategy(
    Weak<Controller::BaseController> controller
): controller(controller) {}
