#include "in_game_event_handler_strategy.h"

#include <utility>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Window.hh>

#include "common/slot_id.h"

#include "game_state_manager.h"

#include "controller/game_controller.h"

#include "event/quit_event.h"
#include "event/movement_event.h"
#include "event/stop_movement_event.h"
#include "event/rotation_event.h"
#include "event/window_resize_event.h"
#include "event/switch_weapon_event.h"
#include "event/switch_context_event.h"

#include "exception/closed_window.h"

void Controller::InGameEventHandlerStrategy::handle_movement_event(Shared<SDL_Event> event) {
    Shared<Model::MovementEvent> movement_event;
    auto key_symbol = event->key.keysym.sym;
    coord_t x_direction = 0;
    coord_t y_direction = 0;

    switch (key_symbol) {
        case SDLK_a:
            x_direction = -1;
            break;
        case SDLK_d:
            x_direction = 1;
            break;
        case SDLK_w:
            y_direction = -1;
            break;
        case SDLK_s:
            y_direction = 1;
            break;
    }

    if (x_direction && !handler_state.moving_horizontally) {
        handler_state.moving_horizontally = true;
        movement_event = make_shared<Model::MovementEvent>(x_direction, 0);
    } else if (y_direction && !handler_state.moving_vertically) {
        handler_state.moving_vertically = true;
        movement_event = make_shared<Model::MovementEvent>(0, y_direction);
    }

    if (!movement_event) {
        return;
    }

    controller.lock()->handle_event(std::move(movement_event));
}

void Controller::InGameEventHandlerStrategy::handle_window_event(Shared<SDL_Event> event) {
    if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
        auto window_resize_event = make_shared<Model::WindowResizeEvent>();
        controller.lock()->handle_event(std::move(window_resize_event));
    }
}

void Controller::InGameEventHandlerStrategy::handle_switch_weapon_event(Shared<SDL_Event> event) {
    if (handler_state.switching_weapon) return;

    Shared<Model::SwitchWeaponEvent> switch_weapon_event;
    auto key_symbol = event->key.keysym.sym;

    Model::SlotID slot_id;

    switch (key_symbol) {
        case SDLK_1:
            slot_id = Model::SlotID::PRIMARY_WEAPON;
            break;
        case SDLK_d:
            slot_id = Model::SlotID::SECONDARY_WEAPON;
            break;
        case SDLK_w:
            slot_id = Model::SlotID::KNIFE;
            break;
        case SDLK_s:
            slot_id = Model::SlotID::BOMB;
            break;
    }

    handler_state.switching_weapon = true;
    switch_weapon_event = make_shared<Model::SwitchWeaponEvent>(slot_id);

    controller.lock()->handle_event(std::move(switch_weapon_event));
}

void Controller::InGameEventHandlerStrategy::handle_switch_context_event(Shared<SDL_Event>) {
    auto switch_context_event = make_shared<Model::SwitchContextEvent>("menu");
    controller.lock()->handle_event(std::move(switch_context_event));
}

void Controller::InGameEventHandlerStrategy::handle_stop_movement_event(Shared<SDL_Event> event) {
    Shared<Model::StopMovementEvent> stop_movement_event;
    auto key_symbol = event->key.keysym.sym;
    bool is_horizontal = false;

    if (key_symbol == SDLK_a || key_symbol == SDLK_d) {
        is_horizontal = true;
    } else if (key_symbol == SDLK_w || key_symbol == SDLK_s) {
        is_horizontal = false;
    } else {
        return;
    }

    if (is_horizontal && handler_state.moving_horizontally) {
        handler_state.moving_horizontally = false;
    } else if (!is_horizontal && handler_state.moving_vertically) {
        handler_state.moving_vertically = false;
    } else {
        return;
    }

    stop_movement_event = make_shared<Model::StopMovementEvent>(is_horizontal);

    controller.lock()->handle_event(std::move(stop_movement_event));
}

void Controller::InGameEventHandlerStrategy::handle_stop_switching_weapon_event() {
    handler_state.switching_weapon = false;
}

void Controller::InGameEventHandlerStrategy::handle_keydown_event(Shared<SDL_Event> event) {
    auto key_symbol = event->key.keysym.sym;
    if (key_symbol == SDLK_ESCAPE) {
        handle_switch_context_event(nullptr);
    } else if (key_symbol == SDLK_w ||
               key_symbol == SDLK_a ||
               key_symbol == SDLK_s ||
               key_symbol == SDLK_d) {
        handle_movement_event(std::move(event));
    } else if (key_symbol == SDLK_1 ||
               key_symbol == SDLK_2 ||
               key_symbol == SDLK_3 ||
               key_symbol == SDLK_4) {
        handle_switch_weapon_event(std::move(event));
    }
}

void Controller::InGameEventHandlerStrategy::handle_keyup_event(Shared<SDL_Event> event) {
    auto key_symbol = event->key.keysym.sym;
    if (key_symbol == SDLK_w ||
        key_symbol == SDLK_a ||
        key_symbol == SDLK_s ||
        key_symbol == SDLK_d) {
        handle_stop_movement_event(std::move(event));
    } else if (key_symbol == SDLK_1 ||
               key_symbol == SDLK_2 ||
               key_symbol == SDLK_3 ||
               key_symbol == SDLK_4) {
        handle_stop_switching_weapon_event();
    }
}

Controller::InGameEventHandlerStrategy::InGameEventHandlerStrategy(Weak<Controller::GameController> controller)
: Controller::EventHandlerStrategy(controller) {}

void Controller::InGameEventHandlerStrategy::handle(Shared<SDL_Event> event) {
    Controller::EventHandlerStrategy::handle(event);
    auto event_type = event->type;

    if (event_type == SDL_QUIT) return;

    if (event_type == SDL_KEYDOWN) {
        handle_keydown_event(event);
    } else if (event_type == SDL_KEYUP) {
        handle_keyup_event(event);
    } else if (event_type == SDL_WINDOWEVENT) {
        handle_window_event(event);
    }
}

void Controller::InGameEventHandlerStrategy::handle_current_game_state(
    Shared<Controller::GameStateManager> game_state_manager
) {
    int mouse_x, mouse_y;
    (void) SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL2pp::Point viewport = game_state_manager->get_camera().get_viewport();

    coord_t dy = mouse_y - (viewport.GetY() / 2);
    coord_t dx = mouse_x - (viewport.GetX() / 2);

    double angle_rad = std::atan2(dy, dx);
    double angle_deg = angle_rad * 180.0 / M_PI;

    angle_deg += 90;

    if (angle_deg < 0) angle_deg += 360;
    if (angle_deg >= 360) angle_deg -= 360;

    angle_t angle = static_cast<angle_t>(angle_deg);

    auto rotation_event = make_shared<Model::RotationEvent>(angle);

    controller.lock()->handle_event(std::move(rotation_event));
}
