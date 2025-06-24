#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "common/DTO/dto_variant.h"
#include "common/definitions.h"
#include "common/queue.h"
#include "common/thread.h"
#include "server/events/events.h"
#include "server/game/game.h"
#include "server/game/game_manager.h"

#include "client_handler_sender.h"
#include "server_protocol.h"

class ClientHandler: public Thread {
private:
    uint8_t player_id = 0;
    std::atomic<bool> is_alive = true;
    Unique<ServerProtocol> protocol;
    GameManager& game_manager;
    Unique<ClientHandlerSender> sender;
    Queue<DTO::DTOVariant>& sender_queue;
    GameQueue* game_queue = nullptr;
    std::string username;

    void handle_create_game(const CreateGameEvent& event);
    void handle_join_game(const JoinGameEvent& event);
    void handle_username(const UsernameEvent& event);
    void handle_list_games();
    void handle_map_request();
    void handle_game_event(const GameEventVariant& event);
    void handle_event(const EventVariant& event);

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;
    ClientHandler(ClientHandler&&) = delete;
    ClientHandler& operator=(ClientHandler&&) = delete;

    void close();

public:
    ClientHandler(Socket&& skt, GameManager& game_manager);

    bool is_dead() const;

    void kill();

    void run() override;

    ~ClientHandler() override;
};

#endif  // CLIENT_HANDLER_H
