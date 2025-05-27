#ifndef CLIENT_GAME_NET_EVENT_SENDER_H
#define CLIENT_GAME_NET_EVENT_SENDER_H

#include "definitions.h"
#include "common/thread.h"

namespace Model {
    class Event;
}

namespace Net {
    class Protocol;
};

namespace Controller {
    class EventSender : public Thread {
    private:
        Net::Protocol& protocol;

    public:
        EventSender(Net::Protocol& protocol) : protocol(protocol) {}

        void run() override;

        ~EventSender() override = default;
    };
};

#endif // CLIENT_GAME_NET_EVENT_SENDER_H
