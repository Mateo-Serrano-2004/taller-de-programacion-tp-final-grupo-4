#include "knife.h"

Knife::Knife()
    : FullWeapon(
        Model::WeaponID::KNIFE,
        Model::SlotID::KNIFE_SLOT,
        1,
        1
    )
{}

std::optional<WeaponShotInfo> Knife::shoot(uint16_t ticks_to_process) {
    if (!triggered || trigger_blocked) {
        return std::nullopt;
    }

    trigger_blocked = true;

    return WeaponShotInfo(
        /* bullets_fired */         1,
        /* base_damage */           35.0f,
        /* min_damage */            35.0f,
        /* max_range */             32.0f,
        /* precision */             1.0f,
        /* dispersion */            0.0f,
        /* damage_mode */           DamageMode::CONSTANT,
        /* falloff_factor */        0.0f,
        /* close_range_threshold */ 0.0f,
        /* close_range_multiplier */1.0f
    );
}