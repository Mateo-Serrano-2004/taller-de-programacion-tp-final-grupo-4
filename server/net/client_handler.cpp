#include "client_handler.h"

#include <iostream>
#include <utility>
#include <variant>
#include <exception>

#include "common/team.h"
#include "common/overloaded.h"
#include "common/DTO/dto_variant.h"

#include "server/exception/invalid_game_exception.h"

void ClientHandler::handle_map_request() {
    sender->get_queue().push(DTO::MapNameListDTO(game_manager.get_name_maps()));
}

void ClientHandler::handle_create_game(const CreateGameEvent& event) {
    game_queue = game_manager.create_game(event.get_party_name(), event.get_map_name(),
                                               username, sender->get_queue());
    player_id = 0;
    sender->get_queue().push(DTO::PlayerIDDTO(player_id));
    sender->get_queue().push(game_manager.get_map(event.get_map_name()));
    sender->get_queue().push(DTO::TeamIDDTO((short_id_t)Model::TeamID::CT));
}

void ClientHandler::handle_join_game(const JoinGameEvent& event) {
    try {
        auto pair = game_manager.join_game(event.get_game_id(), username, sender->get_queue());
        player_id = pair.first;
        game_queue = pair.second;
        sender->get_queue().push(DTO::PlayerIDDTO(player_id));
        sender->get_queue().push(game_manager.get_map(game_manager.get_game_map(event.get_game_id())));
        sender->get_queue().push(DTO::TeamIDDTO(player_id % 2));
    } catch (const InvalidGameException& e) {
        std::cout << "An exception happend\n";
        sender->get_queue().push(DTO::GameStateDTO());
        close();
    }
}

void ClientHandler::handle_username(const UsernameEvent& event) { username = event.get_username(); }

void ClientHandler::handle_list_games() { sender->get_queue().push(DTO::GameListDTO(game_manager.get_games())); }

void ClientHandler::handle_game_event(const GameEventVariant& event) {
    game_queue->push(std::make_pair(player_id, event));

    if (std::holds_alternative<LeaveGameEvent>(event)) {
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
    sender.reset();
}

ClientHandler::ClientHandler(Socket&& skt, GameManager& game_manager)
: protocol(skt), game_manager(game_manager) {
    start();
    sender = make_unique<ClientHandlerSender>(protocol);
}

bool ClientHandler::is_dead() const {
    return !is_alive;
}

void ClientHandler::kill() {
    is_alive = false;
}

void ClientHandler::run() {
    try {
        while (is_alive) {
            EventVariant event = protocol.receive_event();
            handle_event(event);
        }
    } catch (const std::exception&) {
        kill();
    }
}

ClientHandler::~ClientHandler() {
    close();
    join();
}
