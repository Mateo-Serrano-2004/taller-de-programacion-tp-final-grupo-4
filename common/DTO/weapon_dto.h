#ifndef WEAPON_DTO_H
#define WEAPON_DTO_H

#include <cstdint>

namespace DTO {
struct WeaponDTO {
public:
    uint8_t sprite_id;
    uint8_t loaded_ammo;
    uint16_t total_ammo;

    WeaponDTO(
        uint8_t sprite_id,
        uint8_t loaded_ammo,
        uint16_t total_ammo
    );
};
}

#endif  // WEAPON_DTO_H
