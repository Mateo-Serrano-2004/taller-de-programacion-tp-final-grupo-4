#include "update_role_event.h"

#include "common/event_type.h"

Model::UpdateRoleEvent::UpdateRoleEvent(Model::TeamID id):
        Model::Event(Model::EventType::UPDATE_ROLE), id(id) {}

Model::TeamID Model::UpdateRoleEvent::get_team() const { return id; }
