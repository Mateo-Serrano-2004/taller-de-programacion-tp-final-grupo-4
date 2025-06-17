#include "full_weapon.h"

FullWeapon::FullWeapon(Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo, uint16_t total_ammo)
    : Model::Weapon(weapon_id, loaded_ammo, total_ammo), slot_id(slot_id) {}

Model::SlotID FullWeapon::get_slot_id() const {
    return slot_id;
}

void FullWeapon::press_trigger() {
    triggered = true;
}

void FullWeapon::release_trigger() {
    triggered = false;
    trigger_blocked = false;
}