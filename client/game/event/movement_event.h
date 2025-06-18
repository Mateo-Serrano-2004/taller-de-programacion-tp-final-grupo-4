#ifndef CLIENT_EVENT_MOVEMENT_EVENT_H
#define CLIENT_EVENT_MOVEMENT_EVENT_H

#include <cstdint>

#include "common/DTO/event_dto.h"
#include "common/definitions.h"
#include "common/model/vector_2d.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class MovementEvent: public TransferedEvent {
private:
    Physics::Vector2D direction;

public:
    MovementEvent(coord_t x, coord_t y);

    Physics::Vector2D get_direction() const;

    DTO::EventDTO as_dto() override;

    ~MovementEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_MOVEMENT_EVENT_H
