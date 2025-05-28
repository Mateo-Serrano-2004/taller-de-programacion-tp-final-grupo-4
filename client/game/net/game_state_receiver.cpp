#include "game_state_receiver.h"

#include <utility>
#include <atomic>
#include <iostream>

#include "dto_handler/game_state_updater.h"
#include "client/net/client_protocol.h"
#include "common/model/game_state.h"
#include "common/DTO/match_dto.h"
#include "exception/closed_window.h"

Controller::GameStateReceiver::GameStateReceiver(
    std::atomic<bool>& keep_running,
    Model::GameState* game_state,
    Net::ClientProtocol& protocol
): keep_running(keep_running), game_state_updater(game_state), protocol(protocol) {
    start();
}

void Controller::GameStateReceiver::run() {
    bool running = true;
    while (running) {
        try {
            DTO::MatchDTO match_dto = protocol.receive_match_state();
            if (!match_dto.is_valid) {
                running = false;
            } else {
                game_state_updater.update(std::move(match_dto));
            }
        } catch (...) {
            running = false;
        }
    }

    keep_running.store(false);
}

Controller::GameStateReceiver::~GameStateReceiver() {
    stop();
    join();
}
