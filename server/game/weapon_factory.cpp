#include "weapon_factory.h"

#include <memory>

#include "model/ak47.h"
#include "model/awp.h"
#include "model/bomb.h"
#include "model/glock.h"
#include "model/knife.h"
#include "model/m3.h"

Shared<FullWeapon> WeaponFactory::create(Model::WeaponID id) {
    switch (id) {
        case Model::WeaponID::GLOCK:
            return make_shared<Glock>();

        case Model::WeaponID::AK47:
            return make_shared<AK47>();

        case Model::WeaponID::M3:
            return make_shared<M3>();

        case Model::WeaponID::AWP:
            return make_shared<AWP>();

        case Model::WeaponID::KNIFE:
            return make_shared<Knife>();

        case Model::WeaponID::BOMB:
            return make_shared<Bomb>();

        default:
            return nullptr;
    }
}
