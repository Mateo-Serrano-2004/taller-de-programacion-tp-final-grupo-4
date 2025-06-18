#include "stop_movement_event.h"

#include "common/event_type.h"

Model::StopMovementEvent::StopMovementEvent(bool horizontal_movement):
        Model::TransferedEvent(Model::EventType::STOP_MOVEMENT),
        horizontal_movement(horizontal_movement) {}

bool Model::StopMovementEvent::is_horizontal_movement() { return horizontal_movement; }

DTO::EventDTO Model::StopMovementEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_stop_movement_event(this);
}
