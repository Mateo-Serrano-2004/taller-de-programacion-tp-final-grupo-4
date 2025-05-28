#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "common/queue.h"
#include "common/thread.h"
#include "server/game/game.h"
#include "server/game/game_manager.h"
#include "server/events/events.h"

#include "client_handler_sender.h"
#include "server_protocol.h"

class ClientHandler: public Thread {
private:
    ServerProtocol protocol;
    bool is_alive = true;
    GameManager& game_manager;
    GameQueue* game_queue;
    std::string username;
    ClientHandlerSender* sender;
    uint8_t player_id = 0;

    void handle_create_game(const CreateGameEvent& event);
    void handle_join_game(const JoinGameEvent& event);
    void handle_username(const UsernameEvent& event);
    void handle_list_games();
    void handle_map_request();
    void handle_game_event(const GameEventVariant& event);
    void handle_event(const EventVariant& event);

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

public:
    ClientHandler(Socket&& skt, GameManager& game_manager):
            protocol(skt), game_manager(game_manager), game_queue(nullptr), sender(nullptr) {}

    void run() override;
    bool is_dead() const;
    void kill();

    ClientHandler(ClientHandler&&) = default;
    ClientHandler& operator=(ClientHandler&&) = default;

    ~ClientHandler() = default;
};

#endif  // CLIENT_HANDLER_H
