#include "sender.h"

#include <iostream>

#include "common/event_type.h"

#include "dto_handler/event_dto_creator.h"
#include "event/event.h"

#include "client/net/client_protocol.h"

Controller::Sender::Sender(
    SharedQueue<Model::Event>* sender_queue,
    Shared<Net::ClientProtocol> protocol
): sender_queue(sender_queue), protocol(protocol) {
    start();
}

void Controller::Sender::run() {
    bool keep_running = true;
    while (keep_running) {
        try {
            Shared<Model::Event> event = sender_queue->pop();
            if (event->get_type() == Model::EventType::QUIT) {
                std::cout << "Received a QUIT event in Sender\n";
                keep_running = false;
            }
            DTO::EventDTOCreator event_dto_creator(event);
            protocol->send_event(event_dto_creator);
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
    join();
}
