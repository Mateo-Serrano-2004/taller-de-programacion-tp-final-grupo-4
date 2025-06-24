#ifndef SERVER_GAME_MODEL_DROPPED_WEAPON_H
#define SERVER_GAME_MODEL_DROPPED_WEAPON_H

#include "common/DTO/drop_weapon_dto.h"
#include "common/model/vector_2d.h"
#include "server/game/model/full_weapon.h"

class DroppedWeapon {
private:
    Physics::Vector2D position;
    Shared<FullWeapon> weapon;

public:
    DroppedWeapon(Shared<FullWeapon> weapon, const Physics::Vector2D& position);

    const Physics::Vector2D& get_position() const;
    const Shared<FullWeapon>& get_weapon() const;
    DTO::DropWeaponDTO to_dto() const;
};

#endif  // SERVER_GAME_MODEL_DROPPED_WEAPON_H
