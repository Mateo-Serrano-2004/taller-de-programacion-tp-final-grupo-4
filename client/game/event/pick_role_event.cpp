#include "pick_role_event.h"

#include "common/event_type.h"

Model::PickRoleEvent::PickRoleEvent(Model::RoleID role_id):
        Model::TransferedEvent(Model::EventType::PICK_ROLE), role_id(role_id) {}

Model::RoleID Model::PickRoleEvent::get_role_id() const { return role_id; }

DTO::EventDTO Model::PickRoleEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_pick_role_event(this);
}
