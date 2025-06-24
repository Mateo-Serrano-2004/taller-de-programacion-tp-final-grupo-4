#include "stats_event_handler_strategy.h"

#include <memory>
#include <utility>

#include <SDL2/SDL.h>

#include "controller/game_controller.h"
#include "event/switch_context_event.h"

void Controller::StatsEventHandlerStrategy::handle_switch_context_event() {
    auto key_symbol = current_event.key.keysym.sym;
    if (current_event.type == SDL_KEYDOWN) {
        if (key_symbol == SDLK_ESCAPE) {
            auto switch_to_menu = make_shared<Model::SwitchContextEvent>("menu");
            controller.lock()->push_event(std::move(switch_to_menu));
        } else if (key_symbol == SDLK_b) {
            auto switch_to_shop = make_shared<Model::SwitchContextEvent>("shop");
            controller.lock()->push_event(std::move(switch_to_shop));
        }
    } else if (key_symbol == SDLK_TAB) {
        auto switch_to_game = make_shared<Model::SwitchContextEvent>("in-game");
        controller.lock()->push_event(std::move(switch_to_game));
    }
}

Controller::StatsEventHandlerStrategy::StatsEventHandlerStrategy(Weak<GameController> controller):
        Controller::EventHandlerStrategy(controller),
        movement_handler(controller),
        mouse_movement_handler(controller) {}

void Controller::StatsEventHandlerStrategy::handle() {
    Controller::EventHandlerStrategy::handle();

    if (movement_handler.can_handle(current_event))
        movement_handler.handle(current_event);
    else if (current_event.type == SDL_KEYDOWN || current_event.type == SDL_KEYUP)
        handle_switch_context_event();
}

void Controller::StatsEventHandlerStrategy::handle_current_game_state() {
    mouse_movement_handler.notify_current_rotation();
}

void Controller::StatsEventHandlerStrategy::update_on_switch_context() { movement_handler.stop(); }
