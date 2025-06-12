#include "server.h"

#include <string>
#include <memory>
#include <utility>

#include "common/definitions.h"

#include "acceptor.h"

#define EXIT "q"

Server::Server(
    const std::string& port
): socket_pointer(make_unique<Socket>(port.c_str())),
   acceptor(*socket_pointer, game_manager) {}

void Server::launch() {
    acceptor.start();

    std::string input;
    while (input != EXIT) std::getline(std::cin, input);
}

Server::~Server() {
    socket_pointer.reset();
}
