#ifndef CLIENT_GAME_EVENTS_EVENT_H
#define CLIENT_GAME_EVENTS_EVENT_H

#include <cstdint>

#include "event_types.h"

namespace Model {
    class Event {
    private:
        const EventType type;

        Event(const Event&) = delete;
        Event& operator=(const Event&) = delete;
        Event(Event&&) = delete;
        Event& operator=(Event&&) = delete;

    public:
        Event(const EventType type) : type(type) {}

        EventType get_type() const {
            return type;
        }

        virtual ~Event() = default;
    };
}

#endif // CLIENT_GAME_EVENTS_EVENT_H
