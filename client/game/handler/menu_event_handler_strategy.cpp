#include "menu_event_handler_strategy.h"

#include <memory>
#include <utility>

#include <SDL2/SDL.h>

#include "context/menu_context.h"
#include "controller/game_controller.h"
#include "event/quit_event.h"
#include "event/switch_context_event.h"

void Controller::MenuEventHandlerStrategy::handle_switch_context_event() {
    auto switch_context_event = make_shared<Model::SwitchContextEvent>("in-game");
    controller.lock()->push_event(std::move(switch_context_event));
}

void Controller::MenuEventHandlerStrategy::handle_click() {
    context->trigger_buttons(make_shared<SDL_Event>(current_event));
}

void Controller::MenuEventHandlerStrategy::handle_keydown_event() {
    auto key_symbol = current_event.key.keysym.sym;
    if (key_symbol != SDLK_ESCAPE) {
        return;
    }

    handle_switch_context_event();
}

Controller::MenuEventHandlerStrategy::MenuEventHandlerStrategy(
        Weak<Controller::GameController> controller, Context::MenuContext* context):
        Controller::EventHandlerStrategy(controller), context(context) {}

void Controller::MenuEventHandlerStrategy::handle() {
    Controller::EventHandlerStrategy::handle();

    auto event_type = current_event.type;

    if (event_type == SDL_KEYDOWN) {
        handle_keydown_event();
    } else if (event_type == SDL_MOUSEBUTTONDOWN) {
        handle_click();
    }
}
