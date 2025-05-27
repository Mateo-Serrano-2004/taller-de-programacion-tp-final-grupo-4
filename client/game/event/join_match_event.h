#ifndef CLIENT_GAME_EVENTS_JOIN_MATCH_EVENT_H
#define CLIENT_GAME_EVENTS_JOIN_MATCH_EVENT_H

#include <string>
#include <cstdint>

#include "event.h"
#include "event_types.h"

namespace Model {
    class JoinMatchEvent : public Event {
    private:
        uint8_t match_id;

    public:
        JoinMatchEvent(uint8_t match_id) : Event(EventType::JOIN_MATCH), match_id(match_id) {}

        uint8_t get_match_name();

        ~JoinMatchEvent() override = default;
    };
}

#endif // CLIENT_GAME_EVENTS_JOIN_MATCH_EVENT_H
