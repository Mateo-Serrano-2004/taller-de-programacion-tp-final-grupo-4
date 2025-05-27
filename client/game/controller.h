#ifndef CLIENT_GAME_CONTROLLER_H
#define CLIENT_GAME_CONTROLLER_H

#include <memory>

#include "common/definitions.h"

#include "common/thread.h"
#include "event/event.h"

namespace Model {
    class Event;
}

namespace Controller {
    class Controller : public Thread {
    protected:
        SharedQueue<Model::Event> dispatched_events_queue;

        virtual void handle_event(Shared<Model::Event> event) = 0;

    public:
        virtual void dispatch_events() = 0;

        void run() override;

        virtual ~Controller() override;
    };
};

#endif // CLIENT_GAME_CONTROLLER_H
