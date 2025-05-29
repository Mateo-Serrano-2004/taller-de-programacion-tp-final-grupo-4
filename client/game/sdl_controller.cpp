#include "sdl_controller.h"

#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/net/client_protocol.h"
#include "event/event.h"
#include "event/movement_event.h"
#include "event/quit_event.h"
#include "event/rotation_event.h"
#include "exception/closed_window.h"
#include "model/game_state.h"
#include "model/player.h"
#include "window/sdl_window.h"

Controller::SDLController::SDLController(Net::ClientProtocol& protocol, App::SDLWindow* window,
                                         Model::GameState* game_state):
        keep_running(true),
        protocol(protocol),
        window(window),
        game_state(game_state),
        sdl_event_handler(dispatched_events_queue),
        event_sender(keep_running, dispatched_events_queue, protocol),
        game_state_receiver(keep_running, game_state, protocol) {}

void Controller::SDLController::dispatch_events() {
    if (!keep_running) {
        throw App::ClosedWindowException("Received a QUIT event");
    }
    try {
        sdl_event_handler.handle();
    } catch (...) {
        throw App::ClosedWindowException("Received a QUIT event");
    }
}
