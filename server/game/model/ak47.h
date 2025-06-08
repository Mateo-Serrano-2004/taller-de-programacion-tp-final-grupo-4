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

    WeaponDTO to_dto() const override {
        return WeaponDTO{
            static_cast<uint8_t>(WeaponID::AK47),
            0,
            0,
            loaded_ammo,
            total_ammo
        };
    }

    bool can_shoot() const override {
        return loaded_ammo >= 3;
    }

    void shoot() override {
        if (can_shoot()) {
            loaded_ammo -= 3;
        }
    }

    void reload() override {
        loaded_ammo = total_ammo;
    }
};

#endif  // AK47_H