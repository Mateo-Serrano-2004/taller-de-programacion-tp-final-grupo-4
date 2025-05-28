#ifndef CLIENT_EVENT_MOVEMENT_EVENT_H
#define CLIENT_EVENT_MOVEMENT_EVENT_H

#include <cstdint>

#include "event.h"

namespace Model {
    class MovementEvent : public Event {
    private:
        int8_t x_direction;
        int8_t y_direction;
        int8_t speed_type;

    public:
        MovementEvent(int8_t x, int8_t y, int8_t speed_type = 0);

        int8_t get_x_direction() const;
        int8_t get_y_direction() const;
        int8_t get_speed_type() const;

        ~MovementEvent() override = default;
    };
};

#endif // CLIENT_EVENT_MOVEMENT_EVENT_H
