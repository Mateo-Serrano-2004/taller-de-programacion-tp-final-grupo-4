#ifndef CLIENT_EVENT_ROTATION_EVENT_H
#define CLIENT_EVENT_ROTATION_EVENT_H

#include <cstdint>

#include "event.h"
#include "common/definitions.h"

namespace Model {
class RotationEvent: public Event {
private:
    angle_t angle_in_degrees;

public:
    explicit RotationEvent(angle_t angle_in_degrees);

    angle_t get_angle_in_degrees() const;

    ~RotationEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_ROTATION_EVENT_H
