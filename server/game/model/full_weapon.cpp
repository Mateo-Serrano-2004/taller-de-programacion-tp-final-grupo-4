#include "full_weapon.h"

FullWeapon::FullWeapon(
    Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo, uint16_t total_ammo
): Model::Weapon(weapon_id, loaded_ammo, total_ammo),
   slot_id(slot_id), triggered(false), trigger_blocked(false) {}

Model::SlotID FullWeapon::get_slot_id() const { return slot_id; }

void FullWeapon::set_slot_id(Model::SlotID new_slot_id) {
    slot_id = new_slot_id;
}

void FullWeapon::press_trigger() {
    triggered = true;
}

void FullWeapon::release_trigger() {
    triggered = false;
    trigger_blocked = false;
}

bool FullWeapon::shoot(){
    if(!triggered || trigger_blocked) return false;
    uint8_t ammo = get_loaded_ammo();
    if(ammo == 0) return false;
    ammo--;
    set_loaded_ammo(ammo);
    trigger_blocked = true;
    return true;
}