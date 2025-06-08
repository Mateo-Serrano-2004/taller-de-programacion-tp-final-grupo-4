#ifndef AK47_H
#define AK47_H

#include "weapon.h"

class AK47 : public Weapon {
private:
    uint8_t total_ammo = 30;
    uint8_t loaded_ammo = 30;

public:
    AK47() = default;
    ~AK47() override = default;

    WeaponID get_weapon_id() const override {
        return WeaponID::AK47;
    }

    WeaponType get_weapon_type() const override {
        return WeaponType::PRIMARY;
    }

    DTO::WeaponDTO to_dto() const override {
        return DTO::WeaponDTO(
            static_cast<uint8_t>(WeaponID::AK47),
            loaded_ammo,
            total_ammo
        );
    }
};

#endif  // AK47_H