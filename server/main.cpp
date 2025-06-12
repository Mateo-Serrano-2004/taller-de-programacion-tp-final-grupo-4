#include <iostream>

#include "common/definitions.h"
#include "net/server.h"

#define NUM_ARGS 2

int main(int argc, char* argv[]) try {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <port>" << std::endl;
        return ERROR;
    }

    Server server(argv[1]);
    server.launch();

    return SUCCESS;
} catch (const std::exception& e) {
    std::cerr << "Internal server error: " << e.what() << std::endl;
    return ERROR;
}
