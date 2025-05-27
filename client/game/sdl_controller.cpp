#include "sdl_controller.h"

#include <cstdint>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "event/event.h"
#include "event/movement_event.h"
#include "event/rotation_event.h"
#include "event/quit_event.h"
#include "window/sdl_window.h"
#include "exception/closed_window.h"
#include "common/model/game_state.h"
#include "common/model/player.h"

Controller::SDLController::SDLController(
    App::SDLWindow* window,
    Model::GameState* game_state
) : window(window),
    game_state(game_state),
    sdl_event_handler(dispatched_events_queue),
    state_handler(window, game_state, dispatched_events_queue) {
    start();
}

void Controller::SDLController::handle_event(Shared<Model::Event> event) {
    Model::EventType event_type = event->get_type();
    if (event_type == Model::EventType::QUIT) {
        try {
            dispatched_events_queue.close();
        } catch (...) {}
    } else if (event_type == Model::EventType::MOVEMENT) {
        auto movement_event = std::static_pointer_cast<Model::MovementEvent>(event);
        int8_t speed = 3;
        int8_t speed_type = movement_event->get_speed_type();
        if (speed_type == -1) speed = 1;
        else if (speed_type == 1) speed = 5;

        int8_t x = movement_event->get_x_direction() * speed;
        int8_t y = movement_event->get_y_direction() * speed;

        Model::Player& player = game_state->get_reference_player();
        player.set_x(player.get_x() + x);
        player.set_y(player.get_y() + y);
    } else if (event_type == Model::EventType::ROTATION) {
        auto rotation_event = std::static_pointer_cast<Model::RotationEvent>(event);
        int16_t angle_in_degrees = rotation_event->get_angle_in_degrees();
        Model::Player& player = game_state->get_reference_player();
        player.set_angle(angle_in_degrees);
    }
}

void Controller::SDLController::dispatch_events() {
    sdl_event_handler.handle();
    try {
        state_handler.handle();
    } catch (ClosedQueue& error) {
        throw App::ClosedWindowException("Received a QUIT event");
    }
}
