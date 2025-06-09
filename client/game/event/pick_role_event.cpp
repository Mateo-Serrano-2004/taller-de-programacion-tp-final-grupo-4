#include "pick_role_event.h"

#include "common/event_type.h"

Model::PickRoleEvent::PickRoleEvent(Model::RoleID role_id)
: Model::Event(Model::EventType::PICK_ROLE), role_id(role_id) {}

Model::RoleID Model::PickRoleEvent::get_role_id() const { return role_id; }
