#include "event_sender.h"

Controller::EventSender::run() {}

Controller::EventSender::~EventSender() {
    stop();
    join();
}
