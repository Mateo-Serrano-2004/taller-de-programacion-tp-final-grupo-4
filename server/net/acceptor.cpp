#include "acceptor.h"

#include <utility>

void Acceptor::reap() {
    for (auto& client: clients) {
        if (client->is_dead()) {
            client->join();
        }
    }
}

void Acceptor::clear() {
    for (auto& client: clients) {
        client->close();
        client->join();
    }
}

void Acceptor::kill() {
    is_alive = false;
}

void Acceptor::run() {
    while (is_alive) {
        try {
            Socket peer = acceptor.accept();
            auto client = std::make_unique<ClientHandler>(std::move(peer), game_manager);
            reap();
            client->start();
            clients.push_back(std::move(client));
        } catch (...) {
            kill();
        }
    }
}
