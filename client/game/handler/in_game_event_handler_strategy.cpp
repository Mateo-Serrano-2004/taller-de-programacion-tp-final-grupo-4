#include "in_game_event_handler_strategy.h"

#include <cmath>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>

#include "common/round_state.h"
#include "common/slot_id.h"
#include "context/in_game_context.h"
#include "controller/game_controller.h"
#include "event/defuse_bomb_event.h"
#include "event/movement_event.h"
#include "event/quit_event.h"
#include "event/rotation_event.h"
#include "event/stop_defusing_bomb_event.h"
#include "event/stop_movement_event.h"
#include "event/stop_using_weapon_event.h"
#include "event/switch_context_event.h"
#include "event/switch_weapon_event.h"
#include "event/use_weapon_event.h"
#include "utils/mouse_coords_translator.h"

void Controller::InGameEventHandlerStrategy::handle_switch_context_event() {
    auto key_symbol = current_event.key.keysym.sym;
    if (key_symbol == SDLK_ESCAPE) {
        auto switch_to_menu = make_shared<Model::SwitchContextEvent>("menu");
        controller.lock()->push_event(std::move(switch_to_menu));
    } else if (key_symbol == SDLK_b) {
        if (context->current_game_state.round_state != RoundState::Buying)
            return;
        auto switch_to_shop = make_shared<Model::SwitchContextEvent>("shop");
        controller.lock()->push_event(std::move(switch_to_shop));
    } else if (key_symbol == SDLK_TAB) {
        auto switch_to_stats = make_shared<Model::SwitchContextEvent>("stats");
        controller.lock()->push_event(std::move(switch_to_stats));
    }
}

Controller::InGameEventHandlerStrategy::InGameEventHandlerStrategy(
        Weak<Controller::GameController> controller, Context::InGameContext* context):
        Controller::EventHandlerStrategy(controller),
        movement_handler(controller),
        weapon_handler(controller),
        mouse_movement_handler(controller),
        context(context) {}

void Controller::InGameEventHandlerStrategy::handle() {
    Controller::EventHandlerStrategy::handle();

    if (movement_handler.can_handle(current_event))
        movement_handler.handle(current_event);
    else if (weapon_handler.can_handle(current_event))
        weapon_handler.handle(current_event);
    else if (current_event.type == SDL_KEYDOWN)
        handle_switch_context_event();
}

void Controller::InGameEventHandlerStrategy::handle_current_game_state() {
    mouse_movement_handler.notify_current_rotation();
}

void Controller::InGameEventHandlerStrategy::update_on_switch_context(
        const std::string& new_context_name) {
    if (new_context_name != "stats")
        movement_handler.stop();
    weapon_handler.stop();
}
