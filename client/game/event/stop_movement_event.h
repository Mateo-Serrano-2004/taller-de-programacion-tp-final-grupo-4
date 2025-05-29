#ifndef CLIENT_GAME_EVENT_STOP_MOVEMENT_EVENT_H
#define CLIENT_GAME_EVENT_STOP_MOVEMENT_EVENT_H

#include "event.h"

namespace Model {
class StopMovementEvent: public Event {
private:
    bool horizontal_movement;

public:
    explicit StopMovementEvent(bool horizontal_movement);

    bool is_horizontal_movement();

    ~StopMovementEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_STOP_MOVEMENT_EVENT_H
