#include <iostream>

#include "common/definitions.h"
#include "net/server.h"

#define NUM_ARGS 2
#define DEFAULT_CONFIG_FILE "game_config.yaml"

int main(int argc, const char* const argv[]) try {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <port>" << std::endl;
        return ERROR;
    }

    Server server(argv[1], DEFAULT_CONFIG_FILE);
    server.launch();

    return SUCCESS;
} catch (const std::exception& e) {
    std::cerr << "Internal server error: " << e.what() << std::endl;
    return ERROR;
}
