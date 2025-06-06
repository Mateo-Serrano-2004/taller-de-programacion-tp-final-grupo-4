#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <memory>
#include <string>

#include "common/socket.h"
#include "common/thread.h"
#include "server/game/game_manager.h"

#include "client_handler.h"

class Acceptor: public Thread {
private:
    Socket acceptor;
    std::list<std::unique_ptr<ClientHandler>> clients;
    bool is_alive = true;
    GameManager& game_manager;

    void reap();
    void clear();

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

public:
    explicit Acceptor(const std::string& port, GameManager& game_manager):
            acceptor(port.c_str()), game_manager(game_manager) {
        start();
    }
    void kill();
    void run() override;

    Acceptor(Acceptor&&) = default;
    Acceptor& operator=(Acceptor&&) = default;

    ~Acceptor() {
        kill();
        clear();
        join();
    }
};

#endif  // ACCEPTOR_H
