#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <memory>
#include "server/game/model/weapon.h"
#include "common/weapon_type.h"

#include "server/game/model/glock.h"
#include "server/game/model/ak47.h"
#include "server/game/model/m3.h"
#include "server/game/model/awp.h"

class WeaponFactory {
public:
    static std::unique_ptr<Weapon> create(WeaponID id);

    static uint16_t get_price(WeaponID id);

    static bool is_buyable(WeaponID id);
};

#endif // WEAPON_FACTORY_H
