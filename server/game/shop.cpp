#include "shop.h"

#include "common/definitions.h"
#include "common/model/weapon.h"
#include "server/parser/yaml_parser.h"

#include "weapon_factory.h"

Shop::Shop():
        glock_cost(YamlParser::getConfigData().weapons.at("glock").cost),
        ak47_cost(YamlParser::getConfigData().weapons.at("ak-47").cost),
        m3_cost(YamlParser::getConfigData().weapons.at("m3").cost),
        awp_cost(YamlParser::getConfigData().weapons.at("awp").cost),
        primary_ammo_cost(YamlParser::getConfigData().game.costPrimaryAmmo),
        secondary_ammo_cost(YamlParser::getConfigData().game.costSecondaryAmmo) {}

uint16_t Shop::get_cost(Model::WeaponID weapon_id) const {
    switch (weapon_id) {
        case Model::WeaponID::GLOCK:
            return glock_cost;
        case Model::WeaponID::AK47:
            return ak47_cost;
        case Model::WeaponID::AWP:
            return awp_cost;
        case Model::WeaponID::M3:
            return m3_cost;
        default:
            return 0;
    }
}

Shared<FullWeapon> Shop::process_weapon_purchase(FullPlayer& player,
                                                 Model::WeaponID weapon_id) const {
    uint16_t cost = get_cost(weapon_id);

    if (!player.can_pay(cost))
        return nullptr;

    player.substract_money(cost);

    return player.equip_new_weapon_and_drop_previous(WeaponFactory::create(weapon_id));
}

void Shop::process_ammo_purchase(FullPlayer& player, Model::SlotID slot_id) const {
    uint16_t cost;

    if (slot_id == Model::SlotID::PRIMARY_WEAPON) {
        cost = primary_ammo_cost;
    } else if (slot_id == Model::SlotID::SECONDARY_WEAPON) {
        cost = secondary_ammo_cost;
    } else {
        return;
    }

    if (!player.can_pay(cost))
        return;

    player.substract_money(cost);

    player.add_ammo(slot_id);

    return;
}
