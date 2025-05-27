#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "server_protocol.h"

class Server {
private:
    std::string port;
    std::string game_config_path;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

public:
    Server(const std::string& port, const std::string& game_config_path) : port(port), game_config_path(game_config_path) 
    {run();};

    void run();

    Server(Server&&) = default;
    Server& operator=(Server&&) = default;

    ~Server() = default;
};

#endif  // SERVER_H
