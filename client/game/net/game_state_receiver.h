#ifndef CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
#define CLIENT_GAME_NET_GAME_STATE_RECEIVER_H

#include <atomic>

#include "common/thread.h"
#include "dto_handler/game_state_updater.h"

namespace Model {
class GameState;
};

namespace Net {
class ClientProtocol;
};

namespace Controller {
class GameStateReceiver: public Thread {
private:
    std::atomic<bool>& keep_running;
    DTO::GameStateUpdater game_state_updater;
    Net::ClientProtocol* protocol;

public:
    GameStateReceiver(std::atomic<bool>& keep_running, Model::GameState* game_state,
                      Net::ClientProtocol* protocol);

    void run() override;

    ~GameStateReceiver() override;
};
};  // namespace Controller

#endif  // CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
