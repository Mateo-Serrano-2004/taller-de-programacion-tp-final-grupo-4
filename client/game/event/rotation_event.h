#ifndef CLIENT_EVENT_ROTATION_EVENT_H
#define CLIENT_EVENT_ROTATION_EVENT_H

#include <cstdint>

#include "common/DTO/event_dto.h"
#include "common/definitions.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class RotationEvent: public TransferedEvent {
private:
    angle_t angle_in_degrees;

public:
    explicit RotationEvent(angle_t angle_in_degrees);

    angle_t get_angle_in_degrees() const;

    DTO::EventDTO as_dto() override;

    ~RotationEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_ROTATION_EVENT_H
