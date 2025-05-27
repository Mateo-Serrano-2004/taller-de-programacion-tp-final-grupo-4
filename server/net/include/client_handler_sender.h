#ifndef CLIENT_HANDLER_SENDER_H
#define CLIENT_HANDLER_SENDER_H

#include "common/queue.h"
#include "common/thread.h"
#include "../../game/include/game.h"
#include "../../game/include/match_creator.h"

#include "server_protocol.h"

class ClientHandlerSender: public Thread {
private:
    ServerProtocol& protocol;
    Queue<MatchCreator> sender_queue;
    bool is_alive = true;

    ClientHandlerSender(const ClientHandlerSender&) = delete;
    ClientHandlerSender& operator=(const ClientHandlerSender&) = delete;

public:
    explicit ClientHandlerSender(ServerProtocol& protocol): protocol(protocol) { start(); }

    void run() override;
    void kill() { is_alive = false; }
    Queue<MatchCreator>& get_queue() { return sender_queue; }

    ClientHandlerSender(ClientHandlerSender&&) = default;
    ClientHandlerSender& operator=(ClientHandlerSender&&) = default;

    ~ClientHandlerSender() { join(); }
};

#endif  // CLIENT_HANDLER_SENDER_H
