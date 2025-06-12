#ifndef CLIENT_GAME_CONTROLLER_RECEIVER_H
#define CLIENT_GAME_CONTROLLER_RECEIVER_H

#include "common/definitions.h"
#include "common/queue.h"
#include "common/thread.h"

namespace Net {
class ClientProtocol;
};

namespace Controller {
class GameController;
class GameStateManager;

class Receiver: public Thread {
protected:
    GameController* controller;
    Shared<GameStateManager> game_state_manager;
    Shared<Net::ClientProtocol> protocol;

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

public:
    Receiver(
        GameController* controller,
        Shared<Net::ClientProtocol> protocol
    );

    void run() override;

    ~Receiver() override;
};
};

#endif // CLIENT_GAME_CONTROLLER_RECEIVER_H
