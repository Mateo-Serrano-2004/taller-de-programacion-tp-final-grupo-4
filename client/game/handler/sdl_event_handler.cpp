#include "sdl_event_handler.h"

#include <atomic>
#include <memory>

#include "common/definitions.h"
#include "event/event.h"
#include "event/movement_event.h"
#include "event/quit_event.h"
#include "event/stop_movement_event.h"
#include "exception/closed_window.h"

void Controller::SDLEventHandler::handle_quit_event() {
    try {
        event_queue.close();
    } catch (ClosedQueue& error) {
        throw App::ClosedWindowException("Received a QUIT event");
    }
}

void Controller::SDLEventHandler::handle_keydown_event() {
    Shared<Model::MovementEvent> movement_event;
    auto key_symbol = placeholder.key.keysym.sym;
    int8_t x_direction = 0;
    int8_t y_direction = 0;

    switch (key_symbol) {
        case SDLK_LEFT:
            x_direction = -1;
            break;
        case SDLK_RIGHT:
            x_direction = 1;
            break;
        case SDLK_UP:
            y_direction = -1;
            break;
        case SDLK_DOWN:
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

    try {
        event_queue.try_push(movement_event);
    } catch (ClosedQueue& error) {
        throw App::ClosedWindowException("Received a QUIT event");
    }
}

void Controller::SDLEventHandler::handle_keyup_event() {
    Shared<Model::StopMovementEvent> stop_movement_event;
    auto key_symbol = placeholder.key.keysym.sym;
    bool is_horizontal = false;

    if (key_symbol == SDLK_LEFT || key_symbol == SDLK_RIGHT) {
        is_horizontal = true;
    } else if (key_symbol == SDLK_UP || key_symbol == SDLK_DOWN) {
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

    try {
        event_queue.try_push(stop_movement_event);
    } catch (ClosedQueue& error) {
        throw App::ClosedWindowException("Received a QUIT event");
    }
}

Controller::SDLEventHandler::SDLEventHandler(SharedQueue<Model::Event>& queue):
        event_queue(queue) {}

void Controller::SDLEventHandler::handle() {
    while (SDL_PollEvent(&placeholder)) {
        auto event_type = placeholder.type;
        if (event_type == SDL_QUIT) {
            handle_quit_event();
        } else if (event_type == SDL_KEYDOWN) {
            handle_keydown_event();
        } else if (event_type == SDL_KEYUP) {
            handle_keyup_event();
        }
    }
}
