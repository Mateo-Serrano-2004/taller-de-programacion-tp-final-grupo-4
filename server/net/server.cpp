#include "server.h"

#include <filesystem>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/definitions.h"
#include "server/parser/yaml_addresser.h"

#include "acceptor.h"

#define EXIT "q"

Server::Server(const std::string& port, const std::string& config_file):
        maps_names(load_maps()),
        socket_pointer(make_unique<Socket>(port.c_str())),
        game_manager(config_file, maps_names),
        acceptor(*socket_pointer, game_manager) {}

void Server::launch() {
    acceptor.start();

    std::string input;
    while (input != EXIT) std::getline(std::cin, input);
}

std::vector<std::string> Server::load_maps() const {
    YamlAddresser yamlAddresser;
    std::vector<std::string> list_maps_names;
    std::string path = yamlAddresser.get_maps_path();
    for (const auto& entry: std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            auto filePath = entry.path();
            if (filePath.extension() == ".yaml") {
                list_maps_names.push_back(filePath.stem().string());
            }
        }
    }
    return list_maps_names;
}

Server::~Server() { socket_pointer.reset(); }
