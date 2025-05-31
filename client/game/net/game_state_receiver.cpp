#include "game_state_receiver.h"

#include <atomic>
#include <iostream>
#include <utility>

#include "client/net/client_protocol.h"
#include "handler/game_state_manager.h"
#include "exception/closed_window.h"
#include "model/game_state.h"

Controller::GameStateReceiver::GameStateReceiver(std::atomic<bool>& keep_running,
                                                 Controller::GameStateManager* game_state_manager,
                                                 Net::ClientProtocol* protocol):
        keep_running(keep_running), game_state_manager(game_state_manager), protocol(protocol) {
    start();
}

void Controller::GameStateReceiver::run() {
    while (keep_running) {
        try {
            DTO::GameStateDTO game_state_dto = protocol->receive_match_state();
            if (!game_state_dto.is_valid) {
                keep_running = false;
            } else {
                game_state_manager->update(std::move(game_state_dto));
            }
        } catch (...) {
            keep_running = false;
        }
    }
}

Controller::GameStateReceiver::~GameStateReceiver() {
    stop();
    join();
}
