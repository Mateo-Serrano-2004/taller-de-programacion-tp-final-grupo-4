#include "menu_event_handler_strategy.h"

#include <utility>

#include <SDL2/SDL.h>

#include "controller/game_controller.h"
#include "event/quit_event.h"
#include "event/switch_context_event.h"

void Controller::MenuEventHandlerStrategy::handle_quit_event() {
    auto quit_event = make_shared<Model::QuitEvent>();
    controller.lock()->handle_event(std::move(quit_event));
}

void Controller::MenuEventHandlerStrategy::handle_keydown_event(Shared<SDL_Event> event) {
    auto key_symbol = event->key.keysym.sym;
    if (key_symbol != SDLK_ESCAPE) {
        return;
    }

    auto switch_context_event = make_shared<Model::SwitchContextEvent>("in-game");
    controller.lock()->handle_event(std::move(switch_context_event));
}

Controller::MenuEventHandlerStrategy::MenuEventHandlerStrategy(
    Weak<Controller::GameController> controller
): controller(controller) {}

void Controller::MenuEventHandlerStrategy::handle(Shared<SDL_Event> event) {
    auto event_type = event->type;
    if (event_type == SDL_QUIT) {
        handle_quit_event();
    } else if (event_type == SDL_KEYDOWN) {
        handle_keydown_event(std::move(event));
    }
}
