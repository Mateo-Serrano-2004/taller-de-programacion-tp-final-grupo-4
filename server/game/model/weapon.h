#ifndef WEAPON_H
#define WEAPON_H

#include <cstdint>
#include "common/DTO/game_state_dto.h"
#include "common/weapon_type.h"

class Weapon {
public:
    virtual ~Weapon() = default;

    virtual WeaponID get_weapon_id() const = 0;

    virtual WeaponType get_weapon_type() const = 0;

    virtual WeaponDTO to_dto() const = 0;

    virtual bool can_shoot() const = 0;

    virtual void shoot() = 0;

    virtual void reload() = 0;
};

#endif  // WEAPON_H
