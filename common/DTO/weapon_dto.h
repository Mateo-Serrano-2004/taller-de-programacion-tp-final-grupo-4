#ifndef COMMON_DTO_WEAPON_DTO_H
#define COMMON_DTO_WEAPON_DTO_H

#include <cstdint>

#include "common/model/weapon.h"

namespace DTO {
struct WeaponDTO {
public:
    uint8_t weapon_id;
    uint8_t loaded_ammo;
    uint16_t total_ammo;

    WeaponDTO(const WeaponDTO&) = default;

    WeaponDTO();

    WeaponDTO(
        uint8_t weapon_id,
        uint8_t loaded_ammo,
        uint16_t total_ammo
    );

    Model::Weapon to_weapon() const;
};
}

#endif  // COMMON_DTO_WEAPON_DTO_H
