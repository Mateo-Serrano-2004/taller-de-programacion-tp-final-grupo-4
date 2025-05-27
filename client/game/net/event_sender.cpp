#include "event_sender.h"

#include <utils>

#include "event/event.h"
#include "client/net/protocol.h"
#include "common/DTO/event_dto_creator.h"

Controller::EventSender::EventSender(
    SharedQueue<Model::Event>& queue,
    Net::Protocol& protocol
) : event_queue(queue), protocol(protocol) {
    start();
}

Controller::EventSender::run() {
    bool running = true;
    while (running) {
        try {
            Shared<Model::Event> event = event_queue.pop();
            protocol.send_event(std::move(EventDTOCreator(event)));
        } catch (const ClosedQueue& error) {
            running = false;
        } catch (...) {
            // Closed protocol
            running = false;
        }
    }
}

Controller::EventSender::~EventSender() {
    stop();
    join();
}
