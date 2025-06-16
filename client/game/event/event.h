#ifndef CLIENT_GAME_EVENT_EVENT_H
#define CLIENT_GAME_EVENT_EVENT_H

#include <cstdint>

#include "common/event_type.h"

namespace Model {
class Event {
private:
    EventType type;

public:
    explicit Event(EventType type);

    EventType get_type() const;

    virtual ~Event() = default;
};
}  // namespace Model

#endif  // CLIENT_GAME_EVENT_EVENT_H
