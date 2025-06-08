#include "switch_weapon_event.h"

Model::SwitchWeaponEvent::SwitchWeaponEvent(
    Model::SlotID slot_id
): Model::Event(Model::EventType::SWITCH_WEAPON), slot_id(slot_id) {}

Model::SlotID Model::SwitchWeaponEvent::get_slot_id() const { return slot_id; }
