#include "weapon_factory.h"

std::unique_ptr<Weapon> WeaponFactory::create(WeaponID id) {
    switch (id) {
        case WeaponID::GLOCK: return std::make_unique<Glock>();
        case WeaponID::AK47:  return std::make_unique<AK47>();
        case WeaponID::M3:    return std::make_unique<M3>();
        case WeaponID::AWP:   return std::make_unique<AWP>();
        default:              return nullptr;
    }
}

uint16_t WeaponFactory::get_price(WeaponID id) {
    switch (id) {
        case WeaponID::GLOCK: return 300;
        case WeaponID::AK47:  return 800;
        case WeaponID::M3:    return 650;
        case WeaponID::AWP:   return 1000;
        default:              return 9999;
    }
}

bool WeaponFactory::is_buyable(WeaponID id) {
    return id != WeaponID::KNIFE && id != WeaponID::BOMB;
}
