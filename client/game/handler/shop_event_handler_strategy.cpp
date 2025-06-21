#include "shop_event_handler_strategy.h"

#include <memory>

#include <SDL2/SDL.h>

#include "common/event_type.h"
#include "context/shop_context.h"
#include "controller/game_controller.h"
#include "event/switch_context_event.h"

void Controller::ShopEventHandlerStrategy::handle_switch_context_event() {
    auto key_symbol = current_event.key.keysym.sym;

    if (key_symbol == SDLK_ESCAPE) {
        auto switch_to_menu = make_shared<Model::SwitchContextEvent>("menu");
        controller.lock()->push_event(switch_to_menu);
    } else if (key_symbol == SDLK_b) {
        auto switch_to_game = make_shared<Model::SwitchContextEvent>("in-game");
        controller.lock()->push_event(switch_to_game);
    }
}

void Controller::ShopEventHandlerStrategy::handle_click() {
    context->trigger_buttons(make_shared<SDL_Event>(current_event));
}

Controller::ShopEventHandlerStrategy::ShopEventHandlerStrategy(Weak<GameController> controller,
                                                               Context::ShopContext* context):
        Controller::EventHandlerStrategy(controller), context(context) {}

void Controller::ShopEventHandlerStrategy::handle() {
    Controller::EventHandlerStrategy::handle();
    auto event_type = current_event.type;

    if (event_type == SDL_KEYDOWN) {
        handle_switch_context_event();
    } else if (event_type == SDL_MOUSEBUTTONDOWN) {
        handle_click();
    }
}
