#ifndef CLIENT_GAME_NET_EVENT_SENDER_H
#define CLIENT_GAME_NET_EVENT_SENDER_H

#include "common/definitions.h"
#include "common/thread.h"

namespace Model {
class Event;
}

namespace Net {
class ClientProtocol;
};

namespace Controller {
class EventSender: public Thread {
private:
    SharedQueue<Model::Event>* event_queue;
    Net::ClientProtocol* protocol;
    std::atomic<bool>& keep_running;

public:
    EventSender(
        SharedQueue<Model::Event>* queue,
        Net::ClientProtocol* protocol,
        std::atomic<bool>& keep_running
    );

    void run() override;

    ~EventSender() override;
};
};  // namespace Controller

#endif  // CLIENT_GAME_NET_EVENT_SENDER_H
