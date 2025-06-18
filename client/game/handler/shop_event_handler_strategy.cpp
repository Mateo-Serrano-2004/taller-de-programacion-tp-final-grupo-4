#include "shop_event_handler_strategy.h"

#include <memory>

#include <SDL2/SDL.h>

#include "common/event_type.h"
#include "context/shop_context.h"
#include "controller/game_controller.h"
#include "event/switch_context_event.h"

void Controller::ShopEventHandlerStrategy::handle_switch_context_event(Shared<SDL_Event> event) {
    auto key_symbol = event->key.keysym.sym;

    if (key_symbol == SDLK_ESCAPE) {
        auto switch_to_menu = make_shared<Model::SwitchContextEvent>("menu");
        controller.lock()->push_event(switch_to_menu);
    } else if (key_symbol == SDLK_b) {
        auto switch_to_game = make_shared<Model::SwitchContextEvent>("in-game");
        controller.lock()->push_event(switch_to_game);
    }
}

void Controller::ShopEventHandlerStrategy::handle_click(Shared<SDL_Event> event) {
    context->trigger_buttons(event);
}

Controller::ShopEventHandlerStrategy::ShopEventHandlerStrategy(Weak<GameController> controller,
                                                               Context::ShopContext* context):
        Controller::EventHandlerStrategy(controller), context(context) {}

void Controller::ShopEventHandlerStrategy::handle(Shared<SDL_Event> event) {
    Controller::EventHandlerStrategy::handle(event);
    auto event_type = event->type;

    if (event_type == SDL_KEYDOWN) {
        handle_switch_context_event(event);
    } else if (event_type == SDL_MOUSEBUTTONDOWN) {
        handle_click(event);
    }
}
