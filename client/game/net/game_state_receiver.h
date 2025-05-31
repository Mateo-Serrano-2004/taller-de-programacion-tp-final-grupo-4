#ifndef CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
#define CLIENT_GAME_NET_GAME_STATE_RECEIVER_H

#include <atomic>

#include "common/thread.h"

namespace Net {
class ClientProtocol;
};

namespace Controller {
class GameStateManager;

class GameStateReceiver: public Thread {
private:
    std::atomic<bool>& keep_running;
    GameStateManager* game_state_manager;
    Net::ClientProtocol* protocol;

public:
    GameStateReceiver(std::atomic<bool>& keep_running, GameStateManager* game_state_manager,
                      Net::ClientProtocol* protocol);

    void run() override;

    ~GameStateReceiver() override;
};
};  // namespace Controller

#endif  // CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
