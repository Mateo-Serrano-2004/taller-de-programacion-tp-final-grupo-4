#ifndef CLIENT_GAME_CONTROLLER_SENDER_H
#define CLIENT_GAME_CONTROLLER_SENDER_H

#include <atomic>

#include "common/definitions.h"
#include "common/queue.h"
#include "common/thread.h"
#include "event/transfered_event.h"

namespace Net {
class ClientProtocol;
};

namespace Model {
class Event;
};

namespace Controller {
class Sender: public Thread {
protected:
    std::atomic<bool> keep_running;
    SharedQueue<Model::TransferedEvent>* sender_queue;
    Shared<Net::ClientProtocol> protocol;

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

public:
    Sender(SharedQueue<Model::TransferedEvent>* sender_queue, Shared<Net::ClientProtocol> protocol);

    void run() override;

    ~Sender() override;
};
};  // namespace Controller

#endif  // CLIENT_GAME_CONTROLLER_SENDER_H
