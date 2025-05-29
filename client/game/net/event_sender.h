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
    class EventSender : public Thread {
    private:
        std::atomic<bool>& keep_running;
        SharedQueue<Model::Event>& event_queue;
        Net::ClientProtocol& protocol;

    public:
        EventSender(
            std::atomic<bool>& keep_running,
            SharedQueue<Model::Event>& queue,
            Net::ClientProtocol& protocol
        );

        void run() override;

        ~EventSender() override;
    };
};

#endif // CLIENT_GAME_NET_EVENT_SENDER_H
