#ifndef CLIENT_EVENT_QUIT_EVENT_H
#define CLIENT_EVENT_QUIT_EVENT_H

#include "event.h"

namespace Model {
class QuitEvent: public Event {
public:
    QuitEvent(): Event(EventType::QUIT) {}
    ~QuitEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_QUIT_EVENT_H
