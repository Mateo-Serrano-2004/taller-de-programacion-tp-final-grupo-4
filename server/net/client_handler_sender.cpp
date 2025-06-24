#include "client_handler_sender.h"

#include <exception>

ClientHandlerSender::ClientHandlerSender(ServerProtocol& protocol): protocol(protocol) { start(); }

bool ClientHandlerSender::is_dead() const { return !is_alive; }

Queue<DTO::DTOVariant>& ClientHandlerSender::get_queue() { return sender_queue; }

void ClientHandlerSender::kill() { is_alive = false; }

void ClientHandlerSender::close() { sender_queue.close(); }

void ClientHandlerSender::run() {
    while (is_alive) {
        try {
            DTO::DTOVariant game = sender_queue.pop();
            protocol.send_variant(game);
        } catch (const std::exception&) {
            kill();
        }
    }
}

ClientHandlerSender::~ClientHandlerSender() {
    kill();
    close();
    join();
}
