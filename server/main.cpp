#include <iostream>

#include "common/definitions.h"
#include "net/server.h"

#define MIN_ARGS 2
#define MAX_ARGS 3
#define DEFAULT_CONFIG_FILE "game_config.yaml"

int main(int argc, const char* const argv[]) try {

    if (argc < MIN_ARGS || argc > MAX_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <port> [config_file_path](optional)"
                  << std::endl;
        return ERROR;
    }

    Server server(argv[1], argc == MAX_ARGS ? argv[2] : DEFAULT_CONFIG_FILE);
    server.launch();

    return SUCCESS;
} catch (const std::exception& e) {
    std::cerr << "Internal server error: " << e.what() << std::endl;
    return ERROR;
}
