#ifndef GLOCK_H
#define GLOCK_H

#include "weapon.h"

class Glock : public Weapon {
private:
    uint8_t total_ammo = 20;
    uint8_t loaded_ammo = 20;

public:
    Glock() = default;
    ~Glock() override = default;

    WeaponID get_weapon_id() const override {
        return WeaponID::GLOCK;
    }

    WeaponType get_weapon_type() const override {
        return WeaponType::SECONDARY;
    }

    WeaponDTO to_dto() const override {
        return WeaponDTO{
            static_cast<uint8_t>(WeaponID::GLOCK),
            0, // is_shooting
            0, // is_reloading
            loaded_ammo,
            total_ammo // ojo que asi n es realidad quieren la maxima con la cantidad de cargadores.
        };
    }

    bool can_shoot() const override {
        return loaded_ammo > 0;
    }

    void shoot() override {
        if (can_shoot()) {
            --loaded_ammo;
        }
    }

    void reload() override {
        loaded_ammo = total_ammo;
    }
};

#endif  // GLOCK_H
