#include "switch_weapon_event.h"

Model::SwitchWeaponEvent::SwitchWeaponEvent(Model::SlotID slot_id):
        Model::TransferedEvent(Model::EventType::SWITCH_WEAPON), slot_id(slot_id) {}

Model::SlotID Model::SwitchWeaponEvent::get_slot_id() const { return slot_id; }

DTO::EventDTO Model::SwitchWeaponEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_switch_weapon_event(this);
}
