#include "full_weapon.h"

FullWeapon::FullWeapon(Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo,
                       uint8_t max_loaded_ammo, uint16_t total_ammo, uint16_t ticks_to_reload,
                       uint16_t ticks_remaining_to_reload):
        Model::Weapon(weapon_id, loaded_ammo, total_ammo),
        slot_id(slot_id),
        ticks_to_reload(ticks_to_reload),
        ticks_remaining_to_reload(ticks_remaining_to_reload),
        max_loaded_ammo(max_loaded_ammo) {}

Model::SlotID FullWeapon::get_slot_id() const { return slot_id; }

void FullWeapon::press_trigger() { triggered = true; }

void FullWeapon::release_trigger() {
    triggered = false;
    trigger_blocked = false;
}

void FullWeapon::start_reloading() { reloading = true; }

void FullWeapon::stop_reloading() {
    reloading = false;
    ticks_remaining_to_reload = ticks_to_reload;
}

bool FullWeapon::reload(uint16_t ticks_to_process) {
    if (!reloading || get_total_ammo() == 0 || get_loaded_ammo() == max_loaded_ammo)
        return false;

    if (ticks_to_process >= ticks_remaining_to_reload) {
        int needed_ammo = max_loaded_ammo - get_loaded_ammo();
        int bullets_to_load = std::min(needed_ammo, static_cast<int>(get_total_ammo()));

        set_loaded_ammo(get_loaded_ammo() + bullets_to_load);
        set_total_ammo(get_total_ammo() - bullets_to_load);

        stop_reloading();
        return reloading;
    }

    ticks_remaining_to_reload -= ticks_to_process;
    return true;
}

void FullWeapon::add_ammo() { set_total_ammo(get_total_ammo() + max_loaded_ammo); }
