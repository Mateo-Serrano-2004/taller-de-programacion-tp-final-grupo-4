#include "event_sender.h"

#include <utility>
#include <iostream>

#include "common/event/event.h"
#include "client/net/client_protocol.h"
#include "dto_handler/event_dto_creator.h"

#include "exception/closed_window.h"

Controller::EventSender::EventSender(
    SharedQueue<Model::Event>& queue,
    Net::ClientProtocol& protocol
) : event_queue(queue), protocol(protocol) {
    start();
}

void Controller::EventSender::run() {
    bool running = true;
    while (running) {
        try {
            Shared<Model::Event> event = event_queue.pop();
            DTO::EventDTOCreator event_dto_creator(event);
            std::cout << event->get_type() << "\n";
            protocol.send_event(event_dto_creator);
        } catch (...) {
            running = false;
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }
}

Controller::EventSender::~EventSender() {
    stop();
    join();
}
