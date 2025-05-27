#include "../include/acceptor.h"

#include <utility>

void Acceptor::reap() {
    for (auto* client: clients) {
        if (client->is_dead()) {
            client->join();
            delete client;
        }
    }
}

void Acceptor::clear() {
    for (auto* client: clients) {
        client->kill();
        client->join();
        delete client;
    }
    clients.clear();
}

void Acceptor::run() {
    while (is_alive) {
        try {
            Socket peer = acceptor.accept();
            auto* c = new ClientHandler(std::move(peer), game_manager);
            reap();
            clients.push_back(c);
            c->start();
        } catch (...) {
            is_alive = false;
        }
    }
}
