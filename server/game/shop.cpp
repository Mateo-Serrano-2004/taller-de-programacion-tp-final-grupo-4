#include "shop.h"

#include "common/definitions.h"
#include "common/model/weapon.h"

#include "weapon_factory.h"

uint16_t Shop::get_price(Model::WeaponID weapon_id) const {
    switch (weapon_id) {
        case Model::WeaponID::GLOCK:
            return 300;
        case Model::WeaponID::AK47:
            return 650;
        case Model::WeaponID::AWP:
            return 1000;
        case Model::WeaponID::M3:
            return 600;
        default:
            // Cannot happen
            return 0;
    }
}

Shared<FullWeapon> Shop::process_weapon_purchase(FullPlayer& player,
                                                 Model::WeaponID weapon_id) const {
    uint16_t price = get_price(weapon_id);

    if (!player.can_pay(price))
        return nullptr;

    player.substract_money(price);

    return player.equip_new_weapon_and_drop_previous(WeaponFactory::create(weapon_id));
}

void Shop::process_ammo_purchase(FullPlayer& player, Model::SlotID slot_id) const {
    uint16_t price;

    if (slot_id == Model::SlotID::PRIMARY_WEAPON) {
        price = 100;
    } else if (slot_id == Model::SlotID::SECONDARY_WEAPON) {
        price = 75;
    } else {
        return;
    }

    if (!player.can_pay(price))
        return;

    player.substract_money(price);

    player.add_ammo(slot_id);

    return;
}
