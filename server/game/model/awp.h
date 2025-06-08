#ifndef AWP_H
#define AWP_H

#include "weapon.h"

class AWP : public Weapon {
private:
    uint8_t total_ammo = 1;
    uint8_t loaded_ammo = 1;

public:
    AWP() = default;
    ~AWP() override = default;

    WeaponID get_weapon_id() const override {
        return WeaponID::AWP;
    }

    WeaponType get_weapon_type() const override {
        return WeaponType::PRIMARY;
    }

    DTO::WeaponDTO to_dto() const override {
        return DTO::WeaponDTO(
            static_cast<uint8_t>(WeaponID::AWP),
            loaded_ammo,
            total_ammo
        );
    }
};

#endif
