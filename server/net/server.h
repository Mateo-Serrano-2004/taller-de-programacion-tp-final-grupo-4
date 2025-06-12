#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "common/definitions.h"
#include "common/socket.h"

#include "server/game/game_manager.h"

#include "acceptor.h"

class Server {
private:
    GameManager game_manager;
    Unique<Socket> socket_pointer;
    Acceptor acceptor;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

public:
    Server(const std::string& port);

    void launch();

    ~Server();
};

#endif  // SERVER_H
