#include "drop_weapon_event.h"

#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

Model::DropWeaponEvent::DropWeaponEvent(): Model::TransferedEvent(Model::EventType::DROP_WEAPON) {}

DTO::EventDTO Model::DropWeaponEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_drop_weapon_event();
}
