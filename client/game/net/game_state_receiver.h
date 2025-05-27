#ifndef CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
#define CLIENT_GAME_NET_GAME_STATE_RECEIVER_H

#include "common/thread.h"

namespace Net {
    class Protocol;
};

class Controller {
    class GameStateReceiver : public Thread {
    private:
        Net::Protocol& protocol;

    public:
        GameStateReceiver(Net::Protocol& protocol) : protocol(protocol) {}

        void run() override;

        ~GameStateReceiver() override = default;
    };
};

#endif // CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
