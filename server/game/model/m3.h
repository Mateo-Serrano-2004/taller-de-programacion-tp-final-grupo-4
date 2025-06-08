#ifndef M3_H
#define M3_H

#include "weapon.h"

class M3 : public Weapon {
private:
    uint8_t total_ammo = 8;
    uint8_t loaded_ammo = 8;

public:
    M3() = default;
    ~M3() override = default;

    WeaponID get_weapon_id() const override {
        return WeaponID::M3;
    }

    WeaponType get_weapon_type() const override {
        return WeaponType::PRIMARY;
    }

    DTO::WeaponDTO to_dto() const override {
        return DTO::WeaponDTO(
            static_cast<uint8_t>(WeaponID::M3),
            loaded_ammo,
            total_ammo
        );
    }
};

#endif