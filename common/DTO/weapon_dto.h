#ifndef WEAPON_DTO_H
#define WEAPON_DTO_H

#include <cstdint>
#include <string>

struct WeaponDTO {
    uint8_t id;
    uint8_t is_shooting;
    uint8_t is_reloading;
    uint8_t loaded_ammo;
    uint16_t total_ammo;
};

#endif  // WEAPON_DTO_H
