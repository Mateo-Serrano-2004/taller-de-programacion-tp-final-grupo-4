#ifndef CLIENT_EVENT_ROTATION_EVENT_H
#define CLIENT_EVENT_ROTATION_EVENT_H

#include <cstdint>

#include "event.h"

namespace Model {
class RotationEvent: public Event {
private:
    int16_t angle_in_degrees;

public:
    explicit RotationEvent(int16_t angle_in_degrees);

    int16_t get_angle_in_degrees() const;

    ~RotationEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_ROTATION_EVENT_H
