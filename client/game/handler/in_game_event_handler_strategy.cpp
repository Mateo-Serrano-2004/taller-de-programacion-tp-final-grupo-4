#include "in_game_event_handler_strategy.h"

#include "event/movement_event.h"
#include "event/stop_movement_event.h"
#include "exception/closed_window.h"

Shared<Controller::SDLEventHandlerStrategy> Controller::InGameEventHandlerStrategy::handle_keydown_event(Shared<SDL_Event> event) {
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
            return nullptr;
    }

    if (x_direction && !handler_state.moving_horizontally) {
        handler_state.moving_horizontally = true;
        movement_event = make_shared<Model::MovementEvent>(x_direction, 0);
    } else if (y_direction && !handler_state.moving_vertically) {
        handler_state.moving_vertically = true;
        movement_event = make_shared<Model::MovementEvent>(0, y_direction);
    }

    if (!movement_event) {
        return nullptr;
    }

    try {
        dispatched_events_queue->try_push(movement_event);
    } catch (ClosedQueue& error) {
        throw App::ClosedWindowException("Closed communication queue");
    }

    return nullptr;
}

Shared<Controller::SDLEventHandlerStrategy> Controller::InGameEventHandlerStrategy::handle_keyup_event(Shared<SDL_Event> event) {
    Shared<Model::StopMovementEvent> stop_movement_event;
    auto key_symbol = event->key.keysym.sym;
    bool is_horizontal = false;

    if (key_symbol == SDLK_a || key_symbol == SDLK_d) {
        is_horizontal = true;
    } else if (key_symbol == SDLK_w || key_symbol == SDLK_s) {
        is_horizontal = false;
    } else {
        return nullptr;
    }

    if (is_horizontal && handler_state.moving_horizontally) {
        handler_state.moving_horizontally = false;
    } else if (!is_horizontal && handler_state.moving_vertically) {
        handler_state.moving_vertically = false;
    } else {
        return nullptr;
    }

    stop_movement_event = make_shared<Model::StopMovementEvent>(is_horizontal);

    try {
        dispatched_events_queue->try_push(stop_movement_event);
    } catch (ClosedQueue& error) {
        throw App::ClosedWindowException("Closed communication queue");
    }

    return nullptr;
}

Controller::InGameEventHandlerStrategy::InGameEventHandlerStrategy(
    SharedQueue<Model::Event>* dispatched_events_queue
) : Controller::SDLEventHandlerStrategy(dispatched_events_queue) {}

Shared<Controller::SDLEventHandlerStrategy> Controller::InGameEventHandlerStrategy::handle(Shared<SDL_Event> event) {
    auto event_type = event->type;
    if (event_type == SDL_KEYDOWN) {
        return handle_keydown_event(event);
    } else if (event_type == SDL_KEYUP) {
        return handle_keyup_event(event);
    }
    return nullptr;
}
