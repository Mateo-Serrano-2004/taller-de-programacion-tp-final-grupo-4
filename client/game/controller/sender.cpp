#include "sender.h"

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
            auto event_type = event->get_type();
            if (event_type == Model::EventType::QUIT ||
                event_type == Model::EventType::LEAVE_GAME) {
                keep_running = false;
            }
            protocol->send_event(event->as_dto());
        } catch (const std::exception& e) {
            keep_running = false;
        }
    }
}

Controller::Sender::~Sender() {
    keep_running = false;
    join();
}
