#include "client_handler_sender.h"

void ClientHandlerSender::run() {
    while (is_alive) {
        try {
            DTO::GameStateDTO game = sender_queue.pop();
            protocol.send_game_state(game);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            kill();
        }
    }
}
