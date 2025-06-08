#ifndef KNIFE_H
#define KNIFE_H

#include "weapon.h"

class Knife : public Weapon {
public:
    Knife() = default;
    ~Knife() override = default;

    WeaponID get_weapon_id() const override {
        return WeaponID::KNIFE;
    }

    WeaponType get_weapon_type() const override {
        return WeaponType::KNIFE;
    }

    WeaponDTO to_dto() const override {
        return WeaponDTO{
            static_cast<uint8_t>(WeaponID::KNIFE),
            0, // is_shooting NO SE BIEN ACÁ VER CÓMO
            0, // is_reloading
            1, // loaded_ammo
            1  // total_ammo
        };
    }

    bool can_shoot() const override {
        return true;
    }

    void shoot() override {}

    void reload() override {}
};

#endif  // KNIFE_H
