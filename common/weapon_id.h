#ifndef COMMON_WEAPON_ID_H
#define COMMON_WEAPON_ID_H

#include <cstdint>

namespace Model {
enum class WeaponID : uint8_t {
    KNIFE = 0x00,
    GLOCK = 0x01,
    AK47 = 0x02,
    M3 = 0x03,
    AWP = 0x04,
    BOMB = 0x05,

    EMPTY = 0xFF
};
};


#endif  // COMMON_WEAPON_ID_H
