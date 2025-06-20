#ifndef SERVER_GAME_MODEL_WEAPONS_M3_H
#define SERVER_GAME_MODEL_WEAPONS_M3_H

#include "full_weapon.h"
#include "weapon_shot_info.h"

class M3: public FullWeapon {
public:
    M3();

    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
};

#endif  // SERVER_GAME_MODEL_WEAPONS_M3_H
