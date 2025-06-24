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
    int fire_rate;
    int fire_rate_remaining = 0;

public:
    Glock();

    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
};

#endif  // SERVER_GAME_MODEL_WEAPONS_GLOCK_H
