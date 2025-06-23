#include "awp.h"

AWP::AWP():
        FullWeapon(Model::WeaponID::AWP, Model::SlotID::PRIMARY_WEAPON,
                   10,  // loaded_ammo
                   10,
                   20,  // total_ammo
                   120, 120) {}

std::optional<WeaponShotInfo> AWP::shoot(uint16_t ticks_to_process) {
    if (!triggered || trigger_blocked)
        return std::nullopt;

    if (get_loaded_ammo() == 0)
        return std::nullopt;

    set_loaded_ammo(get_loaded_ammo() - 1);
    trigger_blocked = true;

    return WeaponShotInfo(
            /* bullets_fired */ 1,
            /* base_damage */ 100.0f,  // suficiente para matar
            /* min_damage */ 100.0f,   // siempre hace lo mismo
            /* max_range */ 320.0f,    // largo alcance
            /* precision */ 1.0f,
            /* dispersion */ 0.0f,  // casi nada
            /* damage_mode */ DamageMode::CONSTANT,
            /* falloff_factor */ 0.0f,
            /* close_range_threshold */ 0.0f,
            /* close_range_multiplier */ 1.0f);
}
