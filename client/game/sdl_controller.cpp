#include "sdl_controller.h"

#include <cstdint>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/net/client_protocol.h"
#include "event/event.h"
#include "event/movement_event.h"
#include "event/quit_event.h"
#include "event/rotation_event.h"
#include "exception/closed_window.h"
#include "handler/game_state_manager.h"
#include "window/sdl_window.h"

Controller::SDLController::SDLController(Net::ClientProtocol* protocol, App::SDLWindow* window,
                                         Controller::GameStateManager* game_state_manager):
        protocol(protocol),
        window(window),
        game_state_manager(game_state_manager),
        sdl_event_handler(&dispatched_events_queue),
        event_sender(&dispatched_events_queue, protocol, keep_running),
        game_state_receiver(keep_running, game_state_manager, protocol),
        keep_running(true) {}

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
