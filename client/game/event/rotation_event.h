#ifndef CLIENT_GAME_EVENT_ROTATION_EVENT_H
#define CLIENT_GAME_EVENT_ROTATION_EVENT_H

#include <cstdint>

#include "event.h"

namespace Model {
    class RotationEvent : Event {
    private:
        int16_t x_coordinate;
        int16_t y_coordinate;
    
    public:
        RotationEvent(int16_t x, int16_t y);

        int16_t get_x_coordinate() const;
        int16_t get_y_coordinate() const;

        ~RotationEvent() override = default;
    };
};

#endif // CLIENT_GAME_EVENT_ROTATION_EVENT_H
