#include <iostream>

#include "common/definitions.h"
#include "net/server.h"

#define NUM_ARGS 3

int main(int argc, char* argv[]) try {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <port> <game_config_path>" << std::endl;
        return ERROR;
    }

    std::string port(argv[1]);
    std::string game_config_path(argv[2]);

    Controller::Server server(port, game_config_path);

    return SUCCESS;
} catch (const std::exception& e) {
    std::cerr << "Internal server error: " << e.what() << std::endl;
    return ERROR;
}
