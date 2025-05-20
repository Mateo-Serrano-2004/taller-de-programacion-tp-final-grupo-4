#ifndef CLIENT_GAME_CONTROLLER_H
#define CLIENT_GAME_CONTROLLER_H

#include <memory>

#include "client/game/definitions.h"

#include "common/thread.h"
#include "client/game/event/event.h"

namespace Controller {
    class Controller : public Thread {
    protected:
        TSQueue<Event> dispatched_events_queue;

        virtual void handle_event(TS<Event> event) = 0;

    public:
        virtual void dispatch_events() = 0;

        void run() override;

        virtual ~Controller() override;
    };
};

#endif // CLIENT_GAME_CONTROLLER_H
