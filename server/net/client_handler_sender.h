#ifndef CLIENT_HANDLER_SENDER_H
#define CLIENT_HANDLER_SENDER_H

#include "common/DTO/game_state_dto.h"
#include "common/queue.h"
#include "common/thread.h"
#include "server/game/game.h"

#include "server_protocol.h"

class ClientHandlerSender: public Thread {
private:
    ServerProtocol& protocol;
    Queue<DTO::GameStateDTO> sender_queue;
    bool is_alive = true;

    ClientHandlerSender(const ClientHandlerSender&) = delete;
    ClientHandlerSender& operator=(const ClientHandlerSender&) = delete;

public:
    explicit ClientHandlerSender(ServerProtocol& protocol): protocol(protocol) { start(); }

    void run() override;
    void kill() { is_alive = false; }
    Queue<DTO::GameStateDTO>& get_queue() { return sender_queue; }

    ClientHandlerSender(ClientHandlerSender&&) = default;
    ClientHandlerSender& operator=(ClientHandlerSender&&) = default;

    ~ClientHandlerSender() { join(); }
};

#endif  // CLIENT_HANDLER_SENDER_H
