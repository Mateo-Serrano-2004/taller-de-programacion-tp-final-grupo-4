#ifndef CLIENT_EVENT_MOVEMENT_EVENT_H
#define CLIENT_EVENT_MOVEMENT_EVENT_H

#include <cstdint>

#include "common/model/vector_2d.h"
#include "common/definitions.h"
#include "event.h"

namespace Model {
class MovementEvent: public Event {
private:
    Physics::Vector2D direction;

public:
    MovementEvent(coord_t x, coord_t y);

    Physics::Vector2D get_direction() const;

    ~MovementEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_MOVEMENT_EVENT_H
