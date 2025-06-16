#include "rotation_event.h"

#include <cstdint>

Model::RotationEvent::RotationEvent(angle_t angle_in_degrees):
        Model::TransferedEvent(Model::EventType::ROTATION), angle_in_degrees(angle_in_degrees) {}

angle_t Model::RotationEvent::get_angle_in_degrees() const { return angle_in_degrees; }

DTO::EventDTO Model::RotationEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_rotation_event(this);
}
