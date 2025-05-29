#include "server.h"

#include <utility>

#include "server/game/game_manager.h"

#include "acceptor.h"

#define EXIT "q"

Controller::Server::Server(const std::string& port, const std::string& game_config_path):
        port(port), game_config_path(game_config_path) {
    run();
}

void Controller::Server::run() {

    GameManager game_manager(game_config_path);
    Acceptor acceptor(port.c_str(), game_manager);

    std::string input;
    while (input != EXIT) std::getline(std::cin, input);
}
