#ifndef COMMON_EVENT_JOIN_GAME_EVENT_H
#define COMMON_EVENT_JOIN_GAME_EVENT_H

#include <string>
#include <cstdint>

#include "event.h"
#include "event_type.h"

namespace Model {
    class JoinGameEvent : public Event {
    private:
        uint8_t game_id;

    public:
        JoinGameEvent(uint8_t game_id) : Event(EventType::JOIN_GAME), game_id(game_id) {}

        uint8_t get_game_id() const;

        ~JoinGameEvent() override = default;
    };
}

#endif // COMMON_EVENT_JOIN_GAME_EVENT_H
