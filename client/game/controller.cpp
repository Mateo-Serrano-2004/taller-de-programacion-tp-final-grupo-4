#include "client/game/controller.h"

#include <memory>
#include <functional>

#include "event/event.h"

void Controller::Controller::run() {
    bool keep_handling = true;
    while (keep_handling) {
        try {
            Shared<Model::Event> event = dispatched_events_queue.pop();
            handle_event(event);
        } catch (ClosedQueue& error) {
            keep_handling = false;
        }
    }
}

Controller::Controller::~Controller() {
    stop();
    join();
}
