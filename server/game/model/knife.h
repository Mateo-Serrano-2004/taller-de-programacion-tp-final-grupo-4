#ifndef SERVER_GAME_MODEL_WEAPONS_KNIFE_H
#define SERVER_GAME_MODEL_WEAPONS_KNIFE_H

#include "full_weapon.h"
#include "weapon_shot_info.h"

class Knife : public FullWeapon {
public:
    Knife();

    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
};

#endif // SERVER_GAME_MODEL_WEAPONS_KNIFE_H