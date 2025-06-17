#ifndef SERVER_GAME_MODEL_WEAPONS_AWP_H
#define SERVER_GAME_MODEL_WEAPONS_AWP_H

#include "full_weapon.h"
#include "weapon_shot_info.h"

class AWP : public FullWeapon {
public:
    AWP();

    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
};

#endif // SERVER_GAME_MODEL_WEAPONS_AWP_H