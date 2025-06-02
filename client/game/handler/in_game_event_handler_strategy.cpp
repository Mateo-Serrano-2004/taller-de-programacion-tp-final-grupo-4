#include "in_game_event_handler_strategy.h"

#include "controller/game_controller.h"
#include "event/quit_event.h"
#include "event/movement_event.h"
#include "event/stop_movement_event.h"
#include "exception/closed_window.h"

void Controller::InGameEventHandlerStrategy::handle_quit_event() {
    auto quit_event = make_shared<Model::QuitEvent>();
    controller.lock()->handle_event(quit_event);
}

void Controller::InGameEventHandlerStrategy::handle_keydown_event(Shared<SDL_Event> event) {
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
        default:
            return;
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

    controller.lock()->handle_event(movement_event);
}

void Controller::InGameEventHandlerStrategy::handle_keyup_event(Shared<SDL_Event> event) {
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

    controller.lock()->handle_event(stop_movement_event);
}

Controller::InGameEventHandlerStrategy::InGameEventHandlerStrategy(Weak<Controller::GameController> controller)
: Controller::EventHandlerStrategy(), controller(controller) {}

void Controller::InGameEventHandlerStrategy::handle(Shared<SDL_Event> event) {
    auto event_type = event->type;
    if (event_type == SDL_QUIT) {
        handle_quit_event();
    } else if (event_type == SDL_KEYDOWN) {
        handle_keydown_event(event);
    } else if (event_type == SDL_KEYUP) {
        handle_keyup_event(event);
    }
}
