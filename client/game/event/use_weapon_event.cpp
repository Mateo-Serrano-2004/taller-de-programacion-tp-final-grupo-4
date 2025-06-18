#include "use_weapon_event.h"

#include "common/event_type.h"

Model::UseWeaponEvent::UseWeaponEvent(): Model::TransferedEvent(Model::EventType::USE_WEAPON) {}

DTO::EventDTO Model::UseWeaponEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_use_weapon_event();
}
