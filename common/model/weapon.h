#ifndef COMMON_MODEL_WEAPON_H
#define COMMON_MODEL_WEAPON_H

#include <cstdint>

#include "common/DTO/weapon_dto.h"

namespace Model {
class Weapon {
private:
    uint8_t sprite_id;
    uint8_t ammo_in_charger;
    uint16_t total_ammo;

public:
    Weapon(uint8_t sprite_id, uint8_t ammo_in_charger, uint16_t total_ammo);

    uint8_t get_sprite_id() const;
    uint8_t get_ammo_in_charger() const;
    uint16_t get_total_ammo() const;

    void set_sprite_id(uint8_t new_sprite_id);
    void set_ammo_in_charger(uint8_t new_ammo_in_charger);
    void set_total_ammo(uint16_t new_total_ammo);

    Weapon(const Weapon&) = default;
    Weapon& operator =(const Weapon&) = default;
    Weapon(Weapon&&) = default;
    Weapon& operator =(Weapon&&) = default;

    DTO::WeaponDTO to_dto() const;

    ~Weapon() = default;
};
};

#endif // COMMON_MODEL_WEAPON_H
