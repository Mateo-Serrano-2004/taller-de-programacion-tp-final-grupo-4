#include <iostream>

#include "net/include/server.h"

#define NUM_ARGS 3

int main(int argc, char* argv[]) {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <port> <game_config_path>" << std::endl;
        return 1;
    }

    std::string port(argv[1]);
    std::string game_config_path(argv[2]);
    try {
        Server server(port, game_config_path);
    } catch (...) {
        std::cerr << "Internal server error" << std::endl;
        return 1;
    }

    return 0;
}
