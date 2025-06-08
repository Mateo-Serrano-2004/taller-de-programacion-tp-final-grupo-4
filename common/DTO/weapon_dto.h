#ifndef WEAPON_DTO_H
#define WEAPON_DTO_H

#include <cstdint>

namespace DTO {
struct WeaponDTO {
public:
    uint8_t weapon_id;
    uint8_t loaded_ammo;
    uint8_t total_ammo;

    WeaponDTO(const WeaponDTO&) = default;

    WeaponDTO();

    WeaponDTO(
        uint8_t weapon_id,
        uint8_t loaded_ammo,
        uint8_t total_ammo
    );
};
}

#endif  // WEAPON_DTO_H
