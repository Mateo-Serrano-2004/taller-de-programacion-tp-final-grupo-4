#ifndef CLIENT_EVENT_JOIN_GAME_EVENT_H
#define CLIENT_EVENT_JOIN_GAME_EVENT_H

#include <cstdint>
#include <string>

#include "common/definitions.h"
#include "common/event_type.h"

#include "event.h"

namespace Model {
class JoinGameEvent: public Event {
private:
    short_id_t game_id;

public:
    explicit JoinGameEvent(short_id_t game_id): Event(EventType::JOIN_GAME), game_id(game_id) {}

    short_id_t get_game_id() const;

    ~JoinGameEvent() override = default;
};
}  // namespace Model

#endif  // CLIENT_EVENT_JOIN_GAME_EVENT_H
