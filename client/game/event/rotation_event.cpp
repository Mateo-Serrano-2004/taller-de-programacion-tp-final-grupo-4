#include "rotation_event.h"

#include <cstdint>

Model::RotationEvent::RotationEvent(int16_t angle_in_degrees)
: Model::Event(Model::EventType::ROTATION),
  angle_in_degrees(angle_in_degrees) {}

int16_t Model::RotationEvent::get_angle_in_degrees() const { return angle_in_degrees; }
