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
#include "handler/in_game_event_handler_strategy.h"
#include "window/sdl_window.h"

Controller::SDLController::SDLController(Net::ClientProtocol* protocol, App::SDLWindow* window,
                                         Controller::GameStateManager* game_state_manager):
        protocol(protocol),
        window(window),
        game_state_manager(game_state_manager),
        sdl_event_handler(&dispatched_events_queue, make_shared<Controller::InGameEventHandlerStrategy>(&dispatched_events_queue)),
        event_sender(&dispatched_events_queue, protocol),
        game_state_receiver(game_state_manager, protocol) {}

void Controller::SDLController::dispatch_events() {
    try {
        sdl_event_handler.handle();
    } catch (...) {
        throw App::ClosedWindowException("Finished running");
    }
}
