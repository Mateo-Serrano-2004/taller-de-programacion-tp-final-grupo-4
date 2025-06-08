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

    DTO::WeaponDTO to_dto() const override {
        return DTO::WeaponDTO(
            static_cast<uint8_t>(WeaponID::GLOCK),
            loaded_ammo,
            total_ammo // ojo que asi n es realidad quieren la maxima con la cantidad de cargadores.
        );
    }
};

#endif  // GLOCK_H
