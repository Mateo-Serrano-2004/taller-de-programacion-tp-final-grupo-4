#include "sender.h"

#include <iostream>

#include "client/net/client_protocol.h"
#include "common/event_type.h"
#include "event/event.h"

Controller::Sender::Sender(SharedQueue<Model::TransferedEvent>* sender_queue,
                           Shared<Net::ClientProtocol> protocol):
        keep_running(true), sender_queue(sender_queue), protocol(protocol) {
    start();
}

void Controller::Sender::run() {
    while (keep_running) {
        try {
            Shared<Model::TransferedEvent> event = sender_queue->pop();
            if (event->get_type() == Model::EventType::QUIT) {
                std::cout << "Received a QUIT event in Sender\n";
                keep_running = false;
            }
            protocol->send_event(event->as_dto());
        } catch (const ClosedQueue& e) {
            keep_running = false;
        } catch (const std::exception& e) {
            std::cerr << "Sender error: " << e.what() << "\n";
            keep_running = false;
        }
    }
    std::cout << "Finishing sender\n";
}

Controller::Sender::~Sender() {
    keep_running = false;
    join();

    std::cout << "SENDER DESTROYED\n";
}
