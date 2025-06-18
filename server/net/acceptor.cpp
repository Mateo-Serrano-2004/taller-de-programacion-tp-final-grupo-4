#include "acceptor.h"

#include <exception>
#include <utility>

#include "common/definitions.h"

void Acceptor::reap() {
    for (auto& client: clients) {
        if (client && client->is_dead()) {
            client.reset();
        }
    }
}

void Acceptor::clear() {
    for (auto& client: clients) {
        client.reset();
    }
}

Acceptor::Acceptor(Socket& acceptor, GameManager& game_manager):
        acceptor(acceptor), game_manager(game_manager) {}

void Acceptor::kill() { is_alive = false; }

void Acceptor::run() {
    while (is_alive) {
        try {
            Socket peer = acceptor.accept();
            reap();
            auto client = make_unique<ClientHandler>(std::move(peer), game_manager);
            clients.push_back(std::move(client));
        } catch (const std::exception&) {
            kill();
        }
    }
}

Acceptor::~Acceptor() {
    kill();
    clear();
    join();
}
