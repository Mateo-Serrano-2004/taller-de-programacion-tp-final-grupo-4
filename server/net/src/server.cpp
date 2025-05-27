#include "../include/server.h"

#include <utility>

#include "../include/acceptor.h"
#include "../../game/include/game_manager.h"

#define EXIT "q"

void Server::run() {

    GameManager game_manager(game_config_path);
    Acceptor acceptor(port.c_str(), game_manager);

    std::string input;
    while (input != EXIT) std::getline(std::cin, input);
}
