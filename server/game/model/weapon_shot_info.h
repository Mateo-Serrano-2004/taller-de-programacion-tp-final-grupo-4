#ifndef SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H
#define SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H

#include <cstdint>

#include "damage_mode.h"

struct WeaponShotInfo {
    uint8_t bullets_fired;

    float base_damage;
    float min_damage;
    float max_range;

    float precision;
    float dispersion;

    DamageMode damage_mode;
    float falloff_factor;
    float close_range_threshold;
    float close_range_multiplier;

    WeaponShotInfo();

    WeaponShotInfo(uint8_t bullets_fired, float base_damage, float min_damage, float max_range,
                   float precision, float dispersion, DamageMode damage_mode,
                   float falloff_factor = 0.0f, float close_range_threshold = 0.0f,
                   float close_range_multiplier = 1.0f):
            bullets_fired(bullets_fired),
            base_damage(base_damage),
            min_damage(min_damage),
            max_range(max_range),
            precision(precision),
            dispersion(dispersion),
            damage_mode(damage_mode),
            falloff_factor(falloff_factor),
            close_range_threshold(close_range_threshold),
            close_range_multiplier(close_range_multiplier) {}
};

#endif  // SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H
