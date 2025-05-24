#include "rotation_event.h"

#include <cstdint>

Model::RotationEvent::RotationEvent(
    int16_t x,
    int16_t y
) : x_coordinate(x), y_coordinate(y) {}

int16_t Model::RotationEvent::get_x_coordinate() const { return x_coordinate; }

int16_t Model::RotationEvent::get_y_coordinate() const { return y_coordinate; }
