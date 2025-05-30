#include "game_state_receiver.h"

#include <atomic>
#include <iostream>
#include <utility>

#include "client/net/client_protocol.h"
#include "common/DTO/match_dto.h"
#include "dto_handler/game_state_updater.h"
#include "exception/closed_window.h"
#include "model/game_state.h"

Controller::GameStateReceiver::GameStateReceiver(std::atomic<bool>& keep_running,
                                                 Model::GameState* game_state,
                                                 Net::ClientProtocol* protocol):
        keep_running(keep_running), game_state_updater(game_state), protocol(protocol) {
    start();
}

void Controller::GameStateReceiver::run() {
    while (keep_running) {
        try {
            DTO::GameStateDTO match_dto = protocol->receive_match_state();
            if (!match_dto.is_valid) {
                keep_running = false;
            } else {
                game_state_updater.update(match_dto);
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
