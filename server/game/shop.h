#ifndef SERVER_GAME_SHOP_H
#define SERVER_GAME_SHOP_H

#include <cstdint>

#include "common/weapon_id.h"
#include "model/full_player.h"

class Shop {
private:
    uint16_t get_price(Model::WeaponID weapon_id) const;

public:
    Shop() = default;

    Shared<FullWeapon> process_weapon_purchase(FullPlayer& player, Model::WeaponID weapon_id) const;

    ~Shop() = default;
};

#endif  // SERVER_GAME_SHOP_H
