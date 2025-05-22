#include "client/game/sdl_controller.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include <iostream>

#include "exception/closed_window.h"
#include "model/game_state.h"
#include "model/player.h"
#include "event/sdl_keydown_event.h"

Controller::SDLController::SDLController(Model::GameState* game_state)
: game_state(game_state) {
    start();
}

void Controller::SDLController::handle_event(TS<Event> event) {
    TS<SDLEvent> sdl_event = std::static_pointer_cast<SDLEvent>(event);
    const Uint32 event_type = sdl_event->type();
    if (event_type == SDL_QUIT) {
        try {
            dispatched_events_queue.close();
        } catch (...) {}
    }
    if (event_type == SDL_KEYDOWN) {
        TS<SDLKeydownEvent> keydown_event = std::static_pointer_cast<SDLKeydownEvent>(sdl_event);
        const Sint32 key = keydown_event->get_key_sym();
        if (key == SDLK_q) {
            game_state->register_player(Model::Player(80, 90, 3));
        }
    }
}

void Controller::SDLController::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        try {
            dispatched_events_queue.try_push(make_TS<SDLEvent>(placeholder));
        } catch (ClosedQueue& error) {
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }

    uint8_t speed = 3;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LSHIFT]) speed = 5;

    if (state[SDL_SCANCODE_W]) {
        Model::Player& player = game_state->get_players()[0];
        player.set_y(player.get_y() - speed);
    }
    if (state[SDL_SCANCODE_A]) {
        Model::Player& player = game_state->get_players()[0];
        player.set_x(player.get_x() - speed);
    }
    if (state[SDL_SCANCODE_S]) {
        Model::Player& player = game_state->get_players()[0];
        player.set_y(player.get_y() + speed);
    }
    if (state[SDL_SCANCODE_D]) {
        Model::Player& player = game_state->get_players()[0];
        player.set_x(player.get_x() + speed);
    }
}
