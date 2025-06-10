#include "event_handler_strategy.h"

#include <memory>

#include "controller/base_controller.h"

#include "event/quit_event.h"
#include "event/window_resize_event.h"

void Controller::EventHandlerStrategy::handle_quit_event() {
    auto quit_event = make_shared<Model::QuitEvent>();
    controller.lock()->handle_event(quit_event);
}

void Controller::EventHandlerStrategy::handle_window_resize_event() {
    auto window_resize_event = make_shared<Model::WindowResizeEvent>();
    controller.lock()->handle_event(window_resize_event);
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
