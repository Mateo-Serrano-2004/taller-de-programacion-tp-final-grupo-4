#ifndef COMMON_WEAPON_TYPE_H
#define COMMON_WEAPON_TYPE_H

#include <cstdint> 

enum class WeaponID : uint8_t {
    KNIFE = 0,
    GLOCK = 1,
    AK47  = 2,
    M3    = 3,
    AWP   = 4,
    BOMB  = 5
};

enum class WeaponType : uint8_t {
    PRIMARY = 0x00,
    SECONDARY = 0x01,
    KNIFE = 0x02,
    BOMB = 0x03
};

#endif