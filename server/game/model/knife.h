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

    DTO::WeaponDTO to_dto() const override {
        return DTO::WeaponDTO(
            static_cast<uint8_t>(WeaponID::KNIFE),
            1, // loaded_ammo
            1  // total_ammo
        );
    }
};

#endif  // KNIFE_H
