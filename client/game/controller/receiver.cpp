#include "receiver.h"

#include <iostream>

#include "common/DTO/game_state_dto.h"

#include "game_controller.h"

#include "handler/game_state_manager.h"

#include "client/net/client_protocol.h"

Controller::Receiver::Receiver(
    Controller::GameController* controller,
    Net::ClientProtocol* protocol
): controller(controller),
   game_state_manager(controller->get_game_state_manager()),
   protocol(protocol) {
    start();
}

void Controller::Receiver::run() {
    bool keep_running = true;
    while (keep_running) {
        try {
            DTO::GameStateDTO game_state_dto = protocol->receive_match_state();
            if (!game_state_dto.is_valid) {
                keep_running = false;
            } else {
                game_state_manager->update(std::move(game_state_dto));
            }
        } catch (const std::exception& e) {
            std::cerr << "Receiver error: " << e.what() << "\n";
            keep_running = false;
        }
    }
}

Controller::Receiver::~Receiver() {
    stop();
    join();
}
