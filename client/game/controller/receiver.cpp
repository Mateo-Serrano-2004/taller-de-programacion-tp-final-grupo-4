#include "receiver.h"

#include <iostream>
#include <exception>

#include "common/DTO/game_state_dto.h"

#include "client/net/client_protocol.h"

#include "game_controller.h"

#include "handler/game_state_manager.h"

#include "event/end_of_game_event.h"

Controller::Receiver::Receiver(
    Weak<GameController> controller,
    Shared<Net::ClientProtocol> protocol
): keep_running(true),
   controller(controller),
   game_state_manager(controller.lock()->get_game_state_manager()),
   protocol(protocol) {
    start();
}

void Controller::Receiver::run() {
    while (keep_running) {
        try {
            DTO::GameStateDTO game_state_dto = protocol->receive_match_state();
            if (game_state_dto.ended) {
                keep_running = false;
                try {
                    controller.lock()->push_event(make_shared<Model::EndOfGameEvent>());
                } catch (const std::exception&) {}
            } else {
                game_state_manager->update(std::move(game_state_dto));
            }
        } catch (const std::exception& e) {
            std::cerr << "Receiver error: " << e.what() << "\n";
            keep_running = false;
        }
    }
    std::cout << "Finishing receiver\n";
}

Controller::Receiver::~Receiver() {
    keep_running = false;
    join();
}
