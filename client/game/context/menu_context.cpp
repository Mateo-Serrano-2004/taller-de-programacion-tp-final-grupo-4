#include "menu_context.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/Rect.hh>

#include "controller/game_controller.h"
#include "controller/base_controller.h"
#include "exception/closed_window.h"
#include "event/quit_event.h"

void Context::MenuContext::render() {
    background.render();
    exit_button.render();
}

void Context::MenuContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        auto event = make_shared<SDL_Event>(placeholder);

        exit_button.trigger(event);
        event_handler_strategy.handle(event);
    }
}

Context::MenuContext::MenuContext(Weak<Controller::GameController> controller)
: Context::BaseContext("menu", controller),
  event_handler_strategy(controller),
  background(11, controller),
  exit_button(12, controller, &background) {
    background.set_position(SDL2pp::Rect(0, 0, 100, 100));
    exit_button.set_position(SDL2pp::Rect(0, 0, 60, 30));
}
