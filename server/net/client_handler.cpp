#include "client_handler.h"

#include <condition_variable>
#include <exception>
#include <utility>
#include <variant>

#include "common/DTO/dto_variant.h"
#include "common/overloaded.h"
#include "common/team.h"
#include "server/exception/invalid_game_exception.h"
#include "server/parser/yaml_parser.h"

void ClientHandler::handle_map_request() {
    sender_queue.push(DTO::MapNameListDTO(game_manager.get_name_maps()));
}

void ClientHandler::handle_create_game(const CreateGameEvent& event) {
    const ConfigData& config = YamlParser::getConfigData();
    DTO::ConfigDTO config_dto(config.display.width, config.display.height, config.fov.opacity,
                              config.fov.angle, config.fov.ratio);
    auto map = game_manager.get_map(event.get_map_name());
    sender_queue.push(config_dto);
    game_queue = game_manager.create_game(event.get_party_name(), event.get_map_name(), map.second,
                                          username, sender_queue);
    player_id = 0;
    sender_queue.push(DTO::PlayerIDDTO(player_id));
    sender_queue.push(DTO::TeamIDDTO((short_id_t)Model::TeamID::CT));
    sender_queue.push(map.first);
}

void ClientHandler::handle_join_game(const JoinGameEvent& event) {
    try {
        const ConfigData& config = YamlParser::getConfigData();
        DTO::ConfigDTO config_dto(config.display.width, config.display.height, config.fov.opacity,
                                  config.fov.angle, config.fov.ratio);
        sender_queue.push(config_dto);
        auto pair = game_manager.join_game(event.get_game_id(), username, sender_queue);
        player_id = pair.first;
        game_queue = pair.second;
        sender_queue.push(DTO::PlayerIDDTO(player_id));
        auto map = game_manager.get_map(game_manager.get_game_map(event.get_game_id()));
        sender_queue.push(map.first);
        sender_queue.push(DTO::TeamIDDTO(player_id % 2));
    } catch (const InvalidGameException&) {
        sender_queue.push(DTO::GameStateDTO());
        close();
    }
}

void ClientHandler::handle_username(const UsernameEvent& event) { username = event.get_username(); }

void ClientHandler::handle_list_games() {
    sender_queue.push(DTO::GameListDTO(game_manager.get_games()));
}

void ClientHandler::handle_game_event(const GameEventVariant& event) {
    game_queue->push(std::make_pair(player_id, event));

    if (std::holds_alternative<QuitEvent>(event)) {
        close();
    }
}

void ClientHandler::handle_event(const EventVariant& event) {
    std::visit(overloaded{[this](const MapRequestEvent&) { handle_map_request(); },
                          [this](const CreateGameEvent& e) { handle_create_game(e); },
                          [this](const JoinGameEvent& e) { handle_join_game(e); },
                          [this](const UsernameEvent& e) { handle_username(e); },
                          [this](const ListGamesEvent&) { handle_list_games(); },
                          [this](const GameEventVariant& e) { handle_game_event(e); }},
               event);
}

void ClientHandler::close() {
    kill();
    protocol->close_socket();
    join();
    sender.reset();
    protocol.reset();
}

ClientHandler::ClientHandler(Socket&& skt, GameManager& game_manager):
        protocol(std::make_unique<ServerProtocol>(std::move(skt))),
        game_manager(game_manager),
        sender(std::make_unique<ClientHandlerSender>(*protocol)),
        sender_queue(sender->get_queue()) {
    start();
}

bool ClientHandler::is_dead() const { return !is_alive; }

void ClientHandler::kill() { is_alive = false; }

void ClientHandler::run() {
    try {
        while (is_alive) {
            EventVariant event = protocol->receive_event();
            handle_event(event);
        }
    } catch (const std::exception&) {
        kill();
    }
}

ClientHandler::~ClientHandler() { close(); }
