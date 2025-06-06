#include "acceptor.h"

#include <utility>

void Acceptor::reap() {
    for (auto it = clients.begin(); it != clients.end();) {
        if ((*it)->is_dead()) {
            (*it)->join();
            it = clients.erase(it);
        } else {
            ++it;
        }
    }
}

void Acceptor::clear() {
    for (auto& client: clients) {
        client->kill();
        client->join();
    }
    clients.clear();
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
            is_alive = false;
        }
    }
}
