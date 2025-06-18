#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>

#include "common/definitions.h"
#include "common/socket.h"
#include "server/game/game_manager.h"

#include "acceptor.h"

class Server {
private:
    std::vector<std::string> maps_names;
    Unique<Socket> socket_pointer;
    GameManager game_manager;
    Acceptor acceptor;

    std::vector<std::string> load_maps() const;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

public:
    Server(const std::string& port, const std::string& config_file);

    void launch();

    ~Server();
};

#endif  // SERVER_H
