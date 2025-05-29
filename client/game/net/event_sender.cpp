#include "event_sender.h"

#include <atomic>
#include <iostream>
#include <utility>

#include "client/net/client_protocol.h"
#include "dto_handler/event_dto_creator.h"
#include "event/event.h"
#include "exception/closed_window.h"

Controller::EventSender::EventSender(std::atomic<bool>& keep_running,
                                     SharedQueue<Model::Event>& queue,
                                     Net::ClientProtocol& protocol):
        keep_running(keep_running), event_queue(queue), protocol(protocol) {
    start();
}

void Controller::EventSender::run() {
    while (keep_running) {
        try {
            Shared<Model::Event> event = event_queue.pop();
            DTO::EventDTOCreator event_dto_creator(event);
            protocol.send_event(event_dto_creator);
        } catch (...) {
            keep_running = false;
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }
}

Controller::EventSender::~EventSender() {
    std::cout << "Destroying EventSender\n";

    stop();
    join();
}
