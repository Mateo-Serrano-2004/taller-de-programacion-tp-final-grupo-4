#ifndef CLIENT_HANDLER_SENDER_H
#define CLIENT_HANDLER_SENDER_H

#include <atomic>

#include "common/DTO/game_state_dto.h"
#include "common/queue.h"
#include "common/thread.h"

#include "server_protocol.h"

class ClientHandlerSender: public Thread {
private:
    std::atomic<bool> is_alive = true;
    Queue<DTO::GameStateDTO> sender_queue;
    ServerProtocol& protocol;

    ClientHandlerSender(const ClientHandlerSender&) = delete;
    ClientHandlerSender& operator=(const ClientHandlerSender&) = delete;
    ClientHandlerSender(ClientHandlerSender&&) = delete;
    ClientHandlerSender& operator=(ClientHandlerSender&&) = delete;

public:
    explicit ClientHandlerSender(ServerProtocol& protocol);

    bool is_dead() const;
    Queue<DTO::GameStateDTO>& get_queue();

    void kill();
    void close();

    void run() override;

    ~ClientHandlerSender() override;
};

#endif  // CLIENT_HANDLER_SENDER_H
