#include "game_state_receiver.h"

#include <utility>

#include "dto_parser/game_state_updater.h"
#include "client/net/protocol.h"
#include "common/model/game_state.h"
#include "common/dto/match_dto.h"

Controller::GameStateReceiver::GameStateReceiver(
    Model::GameState* game_state,
    Net::Protocol& protocol
): game_state_updater(game_state), protocol(protocol) {
    start();
}

void Controller::GameStateReceiver::run() {
    bool running = true;
    while (running) {
        try {
            MatchDTO match_dto = protocol.receive_match_state();
            game_state_updater.parse(std::move(match_dto));
        } catch (...) {
            running = false;
        }
    }
}

Controller::GameStateReceiver::~GameStateReceiver() {
    stop();
    join();
}
