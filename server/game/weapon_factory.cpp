#include "weapon_factory.h"

#include <memory>

#include "common/model/weapon.h"
#include "common/slot_id.h"

Shared<FullWeapon> WeaponFactory::create(Model::WeaponID id) {
    switch (id) {
        case Model::WeaponID::GLOCK:
            return make_shared<FullWeapon>(id, Model::SlotID::SECONDARY_WEAPON, 20, 20, false, 0);
        case Model::WeaponID::AK47:
            return make_shared<FullWeapon>(id, Model::SlotID::PRIMARY_WEAPON, 45, 45, true, 30);
        case Model::WeaponID::M3:
            return make_shared<FullWeapon>(id, Model::SlotID::PRIMARY_WEAPON, 8, 8, false, 0);
        case Model::WeaponID::AWP:
            return make_shared<FullWeapon>(id, Model::SlotID::PRIMARY_WEAPON, 30, 30, false, 0);
        case Model::WeaponID::KNIFE:
            return make_shared<FullWeapon>(id, Model::SlotID::KNIFE_SLOT, 0, 0, false, 0);
        case Model::WeaponID::BOMB:
            return make_shared<FullWeapon>(id, Model::SlotID::BOMB_SLOT, 0, 0, false, 0);
        default:
            return nullptr;
    }
}
