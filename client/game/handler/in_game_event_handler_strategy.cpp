#include "in_game_event_handler_strategy.h"

#include <cmath>
#include <memory>
#include <utility>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>

#include "common/slot_id.h"
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

#include "game_state_manager.h"

void Controller::InGameEventHandlerStrategy::handle_switch_context_event() {
    auto key_symbol = current_event.key.keysym.sym;
    if (key_symbol == SDLK_ESCAPE) {
        auto switch_to_menu = make_shared<Model::SwitchContextEvent>("menu");
        controller.lock()->push_event(std::move(switch_to_menu));
    } else {
        auto switch_to_shop = make_shared<Model::SwitchContextEvent>("shop");
        controller.lock()->push_event(std::move(switch_to_shop));
    }
}

void Controller::InGameEventHandlerStrategy::handle_keydown_event() {
    auto key_symbol = current_event.key.keysym.sym;
    if (key_symbol == SDLK_ESCAPE || key_symbol == SDLK_b) {
        handle_switch_context_event();
    }
}

Controller::InGameEventHandlerStrategy::InGameEventHandlerStrategy(
        Weak<Controller::GameController> controller):
        Controller::EventHandlerStrategy(controller),
        game_state_manager(controller.lock()->get_game_state_manager()),
        movement_handler(controller),
        weapon_handler(controller) {}

void Controller::InGameEventHandlerStrategy::handle() {
    Controller::EventHandlerStrategy::handle();

    if (movement_handler.can_handle(current_event))
        movement_handler.handle(current_event);
    else if (weapon_handler.can_handle(current_event)) {
        weapon_handler.handle(current_event);
    }
    else {
        auto event_type = current_event.type;

        if (event_type == SDL_KEYDOWN) {
            handle_keydown_event();
        }
    }
}

void Controller::InGameEventHandlerStrategy::handle_current_game_state() {
    auto renderer = controller.lock()->get_renderer();
    auto mouse_coords = MouseCoordsTranslator::get_logical_coords(renderer);

    SDL2pp::Point screen_size = controller.lock()->get_renderer()->GetLogicalSize();

    coord_t dy = mouse_coords.GetY() - (screen_size.GetY() / 2);
    coord_t dx = mouse_coords.GetX() - (screen_size.GetX() / 2);

    double angle_rad = std::atan2(dy, dx);
    double angle_deg = angle_rad * 180.0 / M_PI;

    angle_deg += 90;

    if (angle_deg < 0)
        angle_deg += 360;
    if (angle_deg >= 360)
        angle_deg -= 360;

    angle_t angle = static_cast<angle_t>(angle_deg);

    auto rotation_event = make_shared<Model::RotationEvent>(angle);

    controller.lock()->push_event(std::move(rotation_event));
}

void Controller::InGameEventHandlerStrategy::update_on_switch_context() {
    movement_handler.stop();
    weapon_handler.stop();
}
