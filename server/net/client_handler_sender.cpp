#include "client_handler_sender.h"

void ClientHandlerSender::kill() { is_alive = false; }

bool ClientHandlerSender::is_dead() const { return !is_alive; }

void ClientHandlerSender::run() {
    while (is_alive) {
        try {
            DTO::GameStateDTO game = sender_queue.pop();
            protocol.send_game_state(game);
        } catch (...) {
            kill();
        }
    }
}

void ClientHandlerSender::close() {
    if (is_alive) {
        kill();
        join();
    }
}
