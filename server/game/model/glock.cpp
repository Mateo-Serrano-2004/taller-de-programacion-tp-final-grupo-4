#include "glock.h"

Glock::Glock()
    : FullWeapon(
        Model::WeaponID::GLOCK,
        Model::SlotID::SECONDARY_WEAPON,
        20,     // loaded_ammo
        20,      // total_ammo
        90,
        90
    )
{}

std::optional<WeaponShotInfo> Glock::shoot(uint16_t ticks_to_process) {
    if (!triggered || trigger_blocked) {
        return std::nullopt;
    }

    if (get_loaded_ammo() == 0)
        return std::nullopt;
    set_loaded_ammo(get_loaded_ammo() - 1);
    trigger_blocked = true;
    return WeaponShotInfo(
        /* bullets_fired */         1,
        /* base_damage */           30.0f,
        /* min_damage */            10.0f,
        /* max_range */             200.0f,
        /* precision */             0.9f,
        /* dispersion */            1.0f,
        /* damage_mode */           DamageMode::LINEAR_FALLOFF,
        /* falloff_factor */        0.05f,
        /* close_range_threshold */ 0.0f,
        /* close_range_multiplier */1.0f
    );
}
