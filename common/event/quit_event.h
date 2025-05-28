#ifndef COMMON_EVENT_QUIT_EVENT_H
#define COMMON_EVENT_QUIT_EVENT_H

#include "event.h"

namespace Model {
    class QuitEvent : public Event {
    public:
        QuitEvent() : Event(EventType::QUIT) {}
        ~QuitEvent() override = default;
    };
};

#endif // COMMON_EVENT_QUIT_EVENT_H
