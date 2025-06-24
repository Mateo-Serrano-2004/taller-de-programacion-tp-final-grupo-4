#ifndef SERVER_GAME_MODEL_WEAPONS_BOMB_H
#define SERVER_GAME_MODEL_WEAPONS_BOMB_H

#include "full_weapon.h"
#include "weapon_shot_info.h"

class Bomb: public FullWeapon {
private:
    bool is_planting = false;
    uint16_t planting_ticks = 0;
    bool planted = false;

    uint16_t required_ticks_to_plant;

public:
    Bomb();

    uint8_t get_planting_progress() const;
    void press_trigger() override;
    void release_trigger() override;
    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
    bool reload(uint16_t ticks_to_process) override;
    void add_ammo() override;
    bool is_planted() const;  // creo que no uso
};

#endif  // SERVER_GAME_MODEL_WEAPONS_BOMB_H
