#include "menu_context.h"

#include <iostream>

#include <SDL2/SDL.h>

#include "controller/game_controller.h"
#include "exception/closed_window.h"

void Context::MenuContext::render() {
    menu_renderer.render();
}

void Context::MenuContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        event_handler_strategy.handle(make_shared<SDL_Event>(placeholder));

        if (placeholder.type == SDL_QUIT) {
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }
}

Context::MenuContext::MenuContext(Weak<Controller::GameController> controller)
: Context::BaseContext("menu", controller),
  menu_renderer(controller),
  event_handler_strategy(controller) {}
