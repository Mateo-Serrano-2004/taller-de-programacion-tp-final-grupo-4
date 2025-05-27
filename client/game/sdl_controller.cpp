#include "sdl_controller.h"

#include <cstdint>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "event/event.h"
#include "event/movement_event.h"
#include "event/rotation_event.h"
#include "event/quit_event.h"
#include "window/sdl_window.h"
#include "exception/closed_window.h"
#include "client/net/include/client_protocol.h"
#include "common/model/game_state.h"
#include "common/model/player.h"

Controller::SDLController::SDLController(
    Net::ClientProtocol& protocol,
    App::SDLWindow* window,
    Model::GameState* game_state
) : keep_running(true),
    protocol(protocol),
    window(window),
    game_state(game_state),
    sdl_event_handler(dispatched_events_queue),
    state_handler(window, game_state, dispatched_events_queue),
    event_sender(dispatched_events_queue, protocol),
    game_state_receiver(keep_running, game_state, protocol) {}

void Controller::SDLController::dispatch_events() {
    if (!keep_running) {
        App::ClosedWindowException("Received a QUIT event");
    }
    try {
        sdl_event_handler.handle();
        state_handler.handle();
    } catch (...) {
        throw App::ClosedWindowException("Received a QUIT event");
    }
}
