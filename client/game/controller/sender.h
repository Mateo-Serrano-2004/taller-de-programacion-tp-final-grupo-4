#ifndef CLIENT_GAME_CONTROLLER_SENDER_H
#define CLIENT_GAME_CONTROLLER_SENDER_H

#include <atomic>

#include "common/definitions.h"
#include "common/thread.h"
#include "common/queue.h"

namespace Net {
class ClientProtocol;
};

namespace Model {
class Event;
};

namespace Controller {
class Sender: public Thread {
protected:
    std::atomic<bool>& keep_running;
    SharedQueue<Model::Event>* sender_queue;
    Shared<Net::ClientProtocol> protocol;

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

public:
    Sender(
        std::atomic<bool>& keep_running,
        SharedQueue<Model::Event>* sender_queue,
        Shared<Net::ClientProtocol> protocol
    );

    void run() override;

    ~Sender() override;
};
};

#endif // CLIENT_GAME_CONTROLLER_SENDER_H
