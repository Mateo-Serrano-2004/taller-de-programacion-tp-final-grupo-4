#include "full_weapon.h"

FullWeapon::FullWeapon(
    Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo, uint16_t total_ammo, bool automatic, uint16_t cooldown_ticks
): Model::Weapon(weapon_id, loaded_ammo, total_ammo),
   slot_id(slot_id), triggered(false), trigger_blocked(false), automatic(automatic), cooldown_ticks(cooldown_ticks) {}

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
/*
bool FullWeapon::shoot(){
    if(!triggered || trigger_blocked) return false;
    uint8_t ammo = get_loaded_ammo();
    if(ammo == 0) return false;
    ammo--;
    set_loaded_ammo(ammo);
    if(!automatic) trigger_blocked = true;
    return true;
}
*/
bool FullWeapon::shoot(uint16_t ticks_to_process) {
    if (!triggered || trigger_blocked) {
        ticks_remaining = (ticks_to_process >= ticks_remaining) ? 0 : ticks_remaining - ticks_to_process;
        return false;
    }

    if (ticks_to_process < ticks_remaining) {
        ticks_remaining -= ticks_to_process;
        return false;
    }

    uint8_t ammo = get_loaded_ammo();
    if (ammo == 0) return false;

    ammo--;
    set_loaded_ammo(ammo);

    ticks_remaining = cooldown_ticks;

    if (!automatic)
        trigger_blocked = true;

    return true;
}