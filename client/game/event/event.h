#ifndef COMMON_EVENT_EVENT_H
#define COMMON_EVENT_EVENT_H

#include <cstdint>

#include "common/event_type.h"

namespace Model {
class Event {
private:
    const EventType type;

public:
    explicit Event(const EventType type): type(type) {}

    EventType get_type() const { return type; }

    virtual ~Event() = default;
};
}  // namespace Model

#endif  // COMMON_EVENT_EVENT_H
