#ifndef SERVER_GAME_SHOP_H
#define SERVER_GAME_SHOP_H

#include <cstdint>

#include "common/slot_id.h"
#include "common/weapon_id.h"
#include "model/full_player.h"

class Shop {
private:
    uint16_t glock_cost;
    uint16_t ak47_cost;
    uint16_t m3_cost;
    uint16_t awp_cost;
    uint16_t primary_ammo_cost;
    uint16_t secondary_ammo_cost;
    uint16_t get_cost(Model::WeaponID weapon_id) const;

public:
    Shop();

    Shared<FullWeapon> process_weapon_purchase(FullPlayer& player, Model::WeaponID weapon_id) const;
    void process_ammo_purchase(FullPlayer& player, Model::SlotID slot_id) const;

    ~Shop() = default;
};

#endif  // SERVER_GAME_SHOP_H
