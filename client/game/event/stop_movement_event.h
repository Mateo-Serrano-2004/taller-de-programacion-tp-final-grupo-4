#ifndef CLIENT_GAME_EVENT_STOP_MOVEMENT_EVENT_H
#define CLIENT_GAME_EVENT_STOP_MOVEMENT_EVENT_H

#include "common/DTO/event_dto.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class StopMovementEvent: public TransferedEvent {
private:
    bool horizontal_movement;

public:
    explicit StopMovementEvent(bool horizontal_movement);

    bool is_horizontal_movement();

    DTO::EventDTO as_dto() override;

    ~StopMovementEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_STOP_MOVEMENT_EVENT_H
