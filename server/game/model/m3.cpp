#include "m3.h"

M3::M3():
        FullWeapon(Model::WeaponID::M3, Model::SlotID::PRIMARY_WEAPON,
                   8,  // loaded_ammo
                   8,  // total_ammo
                   100, 100) {}

std::optional<WeaponShotInfo> M3::shoot(uint16_t ticks_to_process) {
    if (!triggered || trigger_blocked) {
        return std::nullopt;
    }

    if (get_loaded_ammo() == 0)
        return std::nullopt;

    set_loaded_ammo(get_loaded_ammo() - 1);
    trigger_blocked = true;

    return WeaponShotInfo(
            /* bullets_fired */ 8,  // 8 perdigones
            /* base_damage */ 8.0f,
            /* min_damage */ 3.0f,
            /* max_range */ 100.0f,
            /* precision */ 0.6f,
            /* dispersion */ 20.0f,  // 17 grados
            /* damage_mode */ DamageMode::SHORT_RANGE_BOOST,
            /* falloff_factor */ 0.15f,
            /* close_range_threshold */ 48.0f,
            /* close_range_multiplier */ 1.75f);
}
