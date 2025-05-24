#include "client/game/sdl_controller.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include <iostream>

#include "window/sdl_window.h"
#include "exception/closed_window.h"
#include "model/game_state.h"
#include "model/player.h"
#include "event/sdl_keydown_event.h"

Controller::SDLController::SDLController(
    Model::GameState* game_state
) : game_state(game_state), m_translator(game_state) {
    start();
}

void Controller::SDLController::handle_event(Shared<Event> event) {
    Shared<SDLEvent> sdl_event = std::static_pointer_cast<SDLEvent>(event);
    const Uint32 event_type = sdl_event->type();
    if (event_type == SDL_QUIT) {
        try {
            dispatched_events_queue.close();
        } catch (...) {}
    }
    if (event_type == SDL_KEYDOWN) {
        Shared<SDLKeydownEvent> keydown_event = std::static_pointer_cast<SDLKeydownEvent>(sdl_event);
        const Sint32 key = keydown_event->get_key_sym();
        if (key == SDLK_q) {
            game_state->register_player(Model::Player(3, 80, 90, 0, 3));
        }
    }
}

void Controller::SDLController::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        try {
            dispatched_events_queue.try_push(make_shared<SDLEvent>(placeholder));
        } catch (ClosedQueue& error) {
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }

    Shared<Model::MovementEvent> k_event = k_translator.get_movement_event();
    Shared<Model::RotationEvent> m_event = m_translator.get_rotation_event();

    if (k_event) {
        int8_t speed = 3;
        int8_t speed_type = k_event->get_speed_type();
        if (speed_type == -1) speed = 1;
        else if (speed_type == 1) speed = 5;

        int8_t x = k_event->get_x_direction() * speed;
        int8_t y = k_event->get_y_direction() * speed;

        Model::Player& player = game_state->get_players()[0];
        player.set_x(player.get_x() + x);
        player.set_y(player.get_y() + y);
    }

    if (m_event) {
        int16_t x = m_event->get_x_coordinate();
        int16_t y = m_event->get_y_coordinate();
        Model::Player& player = game_state->get_players()[0];
        player.set_angle(x, y, 320 - 15, 240 - 15);
    }

    // const Uint8* state = SDL_GetKeyboardState(NULL);

    // if (state[SDL_SCANCODE_LSHIFT]) speed = 5;

    // if (state[SDL_SCANCODE_W]) {
    //     Model::Player& player = game_state->get_players()[0];
    //     player.set_y(player.get_y() - speed);
    // }
    // if (state[SDL_SCANCODE_A]) {
    //     Model::Player& player = game_state->get_players()[0];
    //     player.set_x(player.get_x() - speed);
    // }
    // if (state[SDL_SCANCODE_S]) {
    //     Model::Player& player = game_state->get_players()[0];
    //     player.set_y(player.get_y() + speed);
    // }
    // if (state[SDL_SCANCODE_D]) {
    //     Model::Player& player = game_state->get_players()[0];
    //     player.set_x(player.get_x() + speed);
    // }
}
