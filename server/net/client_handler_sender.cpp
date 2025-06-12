#include "client_handler_sender.h"

#include <exception>

ClientHandlerSender::ClientHandlerSender(ServerProtocol& protocol)
: protocol(protocol) {
    start();
}

bool ClientHandlerSender::is_dead() const { return !is_alive; }

Queue<DTO::GameStateDTO>& ClientHandlerSender::get_queue() { return sender_queue; }

void ClientHandlerSender::kill() { is_alive = false; }

void ClientHandlerSender::close() {
    sender_queue.close();
    join();
}

void ClientHandlerSender::run() {
    while (is_alive) {
        try {
            DTO::GameStateDTO game = sender_queue.pop();
            protocol.send_game_state(game);
        } catch (const std::exception&) {
            kill();
        }
    }
}

ClientHandlerSender::~ClientHandlerSender() {
    close();
}
