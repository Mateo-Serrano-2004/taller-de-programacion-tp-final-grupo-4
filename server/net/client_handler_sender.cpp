#include "client_handler_sender.h"

void ClientHandlerSender::run() {
    while (is_alive) {
        try {
            DTO::GameStateDTO game = sender_queue.pop();
            protocol.send_match_state(game);
        } catch (const ClosedQueue&) {
            break;
        }
    }
}
