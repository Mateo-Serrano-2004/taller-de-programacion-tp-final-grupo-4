#include "../include/client_handler.h"

#include <variant>
#include <iostream>

#include "../../events/overloaded.h"
#include "../../game/include/match_creator.h"

void ClientHandler::handle_map_request() {
    protocol.send_all_maps_names(game_manager.get_name_maps());
}

void ClientHandler::handle_create_game(const CreateGameEvent& event) {
    sender = new ClientHandlerSender(protocol);
    uint8_t game_id = game_manager.create_game(event.get_party_name(), event.get_map_name(),
                                               username, sender->get_queue());
    player_id = 0;
    game_queue = game_manager.get_game_queue(game_id);
    protocol.send_player_id(player_id);
    // protocol.send_map(game_manager.get_game_map(game_id));
}

void ClientHandler::handle_join_game(const JoinGameEvent& event) {
    sender = new ClientHandlerSender(protocol);
    player_id = game_manager.join_game(event.get_game_id(), username, sender->get_queue());
    game_queue = game_manager.get_game_queue(event.get_game_id());
    protocol.send_player_id(player_id);
    // protocol.send_map(game_manager.get_game_map(event.get_game_id()));
}

void ClientHandler::handle_username(const SendUsernameEvent& event) {
    username = event.get_username();
}

void ClientHandler::handle_list_games() { protocol.send_games(game_manager.get_games()); }

void ClientHandler::handle_game_event(const GameEventVariant& event) {
    if (std::holds_alternative<LeaveGameEvent>(event)) {
        protocol.send_match_state(MatchCreator());
        delete sender;
    } else {
        game_queue->push(std::make_pair(player_id, event));
    }
}

void ClientHandler::handle_event(const EventVariant& event) {
    std::visit(overloaded{[this](const MapRequestEvent&) { handle_map_request(); },
                          [this](const CreateGameEvent& e) { handle_create_game(e); },
                          [this](const JoinGameEvent& e) { handle_join_game(e); },
                          [this](const SendUsernameEvent& e) { handle_username(e); },
                          [this](const ListGamesEvent&) { handle_list_games(); },
                          [this](const GameEventVariant& e) { handle_game_event(e); }},
               event);
}

void ClientHandler::run() {
    try {
        while (is_alive) {
            EventVariant event = protocol.receive_event();
            handle_event(event);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        kill();
    }
}

void ClientHandler::kill() { is_alive = false; }

bool ClientHandler::is_dead() const { return !is_alive; }
