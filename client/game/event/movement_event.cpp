#include "movement_event.h"

Model::MovementEvent::MovementEvent(int8_t x, int8_t y, int8_t speed):
        Model::Event(Model::EventType::MOVEMENT),
        x_direction(x),
        y_direction(y),
        speed_type(speed) {}

int8_t Model::MovementEvent::get_x_direction() const { return x_direction; }

int8_t Model::MovementEvent::get_y_direction() const { return y_direction; }

int8_t Model::MovementEvent::get_speed_type() const { return speed_type; }
