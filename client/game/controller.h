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
    class Controller {
    protected:
        SharedQueue<Model::Event> dispatched_events_queue;

    public:
        virtual void dispatch_events() = 0;

        virtual ~Controller() = default;
    };
};

#endif // CLIENT_GAME_CONTROLLER_H
