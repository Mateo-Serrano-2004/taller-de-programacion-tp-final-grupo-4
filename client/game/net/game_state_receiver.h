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
    GameStateManager* game_state_manager;
    Net::ClientProtocol* protocol;

public:
    GameStateReceiver(GameStateManager* game_state_manager,
                      Net::ClientProtocol* protocol);

    void run() override;

    ~GameStateReceiver() override;
};
};  // namespace Controller

#endif  // CLIENT_GAME_NET_GAME_STATE_RECEIVER_H
