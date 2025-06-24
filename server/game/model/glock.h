#ifndef SERVER_GAME_MODEL_WEAPONS_GLOCK_H
#define SERVER_GAME_MODEL_WEAPONS_GLOCK_H

#include "full_weapon.h"
#include "weapon_shot_info.h"

class Glock: public FullWeapon {
private:
    float damage;
    float precision;
    int range;
    int bullets_per_shot;
    float dispersion;
    float falloff_factor;
    float close_range_threshold;
    float close_range_multiplier;
    int fire_rate;
    int fire_rate_remaining;
    int min_damage;

public:
    Glock();

    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
};

#endif  // SERVER_GAME_MODEL_WEAPONS_GLOCK_H
