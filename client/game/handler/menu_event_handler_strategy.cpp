#include "menu_event_handler_strategy.h"

#include <utility>

#include <SDL2/SDL.h>

#include "controller/game_controller.h"

#include "context/menu_context.h"

#include "event/quit_event.h"
#include "event/switch_context_event.h"

#include "entity/rendered.h"

void Controller::MenuEventHandlerStrategy::handle_switch_context_event(Shared<SDL_Event>) {
    auto switch_context_event = make_shared<Model::SwitchContextEvent>("in-game");
    controller.lock()->handle_event(std::move(switch_context_event));
}

void Controller::MenuEventHandlerStrategy::handle_click(Shared<SDL_Event> event) {
    context->trigger_buttons(event);
}

void Controller::MenuEventHandlerStrategy::handle_keydown_event(Shared<SDL_Event> event) {
    auto key_symbol = event->key.keysym.sym;
    if (key_symbol != SDLK_ESCAPE) {
        return;
    }

    handle_switch_context_event(nullptr);
}

Controller::MenuEventHandlerStrategy::MenuEventHandlerStrategy(
    Weak<Controller::GameController> controller,
    Context::MenuContext* context
): Controller::EventHandlerStrategy(controller), context(context) {}

void Controller::MenuEventHandlerStrategy::handle(Shared<SDL_Event> event) {
    Controller::EventHandlerStrategy::handle(event);

    auto event_type = event->type;

    if (event_type == SDL_KEYDOWN) {
        handle_keydown_event(std::move(event));
    } else if (event_type == SDL_MOUSEBUTTONDOWN) {
        handle_click(event);
    }
}
