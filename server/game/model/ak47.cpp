#include "ak47.h"

AK47::AK47()
    : FullWeapon(
        Model::WeaponID::AK47,
        Model::SlotID::PRIMARY_WEAPON,
        30, // loaded_ammo
        30  // total_ammo
    )
{}

void AK47::press_trigger() {
    triggered = true;
    if (!in_burst && get_loaded_ammo() > 0) {
        in_burst = true;
        bullets_in_current_burst = 0;
        ticks_until_next_bullet = 0;
    }
}

void AK47::release_trigger() {
    triggered = false;
    trigger_blocked = false;
    in_burst = false;
    bullets_in_current_burst = 0;
    ticks_until_next_bullet = 0;
}

std::optional<WeaponShotInfo> AK47::shoot(uint16_t ticks_to_process) {
    if (!triggered) return std::nullopt;
    if (!in_burst) return std::nullopt;

    if (ticks_until_next_bullet > ticks_to_process) {
        ticks_until_next_bullet -= ticks_to_process;
        return std::nullopt;
    }

    if (bullets_in_current_burst >= 3) {
        in_burst = false;
        ticks_until_next_bullet = burst_cooldown_ticks;
        return std::nullopt;
    }

    if (get_loaded_ammo() == 0) {
        in_burst = false;
        return std::nullopt;
    }

    set_loaded_ammo(get_loaded_ammo() - 1);
    bullets_in_current_burst++;
    ticks_until_next_bullet = ticks_between_burst_bullets;

    return WeaponShotInfo(
        1,          // bullets_fired
        22.0f,      // base_damage
        8.0f,       // min_damage
        100.0f,      // max_range
        0.75f,      // precision
        0.07f,      // dispersion
        DamageMode::LINEAR_FALLOFF,
        0.035f,     // falloff_factor
        0.0f,       // close_range_threshold
        1.0f        // close_range_multiplier
    );
}