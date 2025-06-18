#include "stop_using_weapon_event.h"

#include "common/event_type.h"

Model::StopUsingWeaponEvent::StopUsingWeaponEvent():
        Model::TransferedEvent(Model::EventType::STOP_USING_WEAPON) {}

DTO::EventDTO Model::StopUsingWeaponEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_stop_using_weapon_event();
}
