#include <iostream>

#include "common/definitions.h"
#include "lobby/lobby_app.h"

#define NUM_ARGS 1

int main(int argc, char* argv[]) try {
    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << ". No need more arguments" << std::endl;
        return ERROR;
    }

    App::LobbyApp lobby_app(argc, argv);

    return SUCCESS;
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return ERROR;
}
