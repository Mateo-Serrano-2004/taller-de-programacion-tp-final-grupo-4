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
        } else if (key == SDLK_w) {
            Model::Player& player = game_state->get_players()[0];
            player.set_y(player.get_y() - 1);
        } else if (key == SDLK_a) {
            Model::Player& player = game_state->get_players()[0];
            player.set_x(player.get_x() - 1);
        } else if (key == SDLK_s) {
            Model::Player& player = game_state->get_players()[0];
            player.set_y(player.get_y() + 1);
        } else if (key == SDLK_d) {
            Model::Player& player = game_state->get_players()[0];
            player.set_x(player.get_x() + 1);
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
}
