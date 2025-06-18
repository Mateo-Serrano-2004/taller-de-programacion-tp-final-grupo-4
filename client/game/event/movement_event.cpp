#include "movement_event.h"

Model::MovementEvent::MovementEvent(coord_t x, coord_t y):
        Model::TransferedEvent(Model::EventType::MOVEMENT), direction(x, y) {}

Physics::Vector2D Model::MovementEvent::get_direction() const { return direction; }

DTO::EventDTO Model::MovementEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_movement_event(this);
}
