#ifndef CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
#define CLIENT_GAME_NET_GAME_STATE_RECEIVER_H

#include "dto_handler/game_state_updater.h"
#include "common/thread.h"

class Model {
    class GameState;
};

namespace Net {
    class Protocol;
};

class Controller {
    class GameStateReceiver : public Thread {
    private:
        GameStateUpdater game_state_updater;
        Net::Protocol& protocol;

    public:
        GameStateReceiver(
            Model::GameState* game_state,
            Net::Protocol& protocol
        );

        void run() override;

        ~GameStateReceiver() override;
    };
};

#endif // CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
