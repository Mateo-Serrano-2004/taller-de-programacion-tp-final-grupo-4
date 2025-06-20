#ifndef SERVER_GAME_WEAPON_FACTORY_H
#define SERVER_GAME_WEAPON_FACTORY_H

#include <cstdint>

#include "common/definitions.h"
#include "common/weapon_id.h"
#include "model/full_weapon.h"

namespace Model {
class Weapon;
};

class WeaponFactory {
public:
    static Shared<FullWeapon> create(Model::WeaponID id);
};

#endif  // SERVER_GAME_WEAPON_FACTORY_H
