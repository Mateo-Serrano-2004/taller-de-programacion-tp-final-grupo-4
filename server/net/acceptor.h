#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <memory>
#include <string>

#include "common/definitions.h"
#include "common/socket.h"
#include "common/thread.h"
#include "server/game/game_manager.h"

#include "client_handler.h"

class Acceptor: public Thread {
private:
    std::list<Unique<ClientHandler>> clients;
    bool is_alive = true;
    Socket& acceptor;
    GameManager& game_manager;

    void reap();
    void clear();

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;
    Acceptor(Acceptor&&) = delete;
    Acceptor& operator=(Acceptor&&) = delete;

public:
    Acceptor(Socket& acceptor, GameManager& game_manager);

    void kill();
    void run() override;

    ~Acceptor() override;
};

#endif  // ACCEPTOR_H
