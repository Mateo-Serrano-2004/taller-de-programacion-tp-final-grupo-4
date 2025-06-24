#ifndef SERVER_GAME_MODEL_WEAPONS_AK47_H
#define SERVER_GAME_MODEL_WEAPONS_AK47_H

#include "full_weapon.h"
#include "weapon_shot_info.h"

class AK47: public FullWeapon {
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
    bool in_burst;
    uint8_t bullets_in_current_burst;
    uint16_t ticks_until_next_bullet;
    uint16_t ticks_between_burst_bullets;
    uint16_t burst_cooldown_ticks;

public:
    AK47();
    void press_trigger() override;
    void release_trigger() override;
    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
};

#endif  // SERVER_GAME_MODEL_WEAPONS_AK47_H
