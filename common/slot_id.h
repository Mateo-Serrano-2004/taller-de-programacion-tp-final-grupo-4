#ifndef COMMON_SLOT_ID_H
#define COMMON_SLOT_ID_H

#include <cstdint>

namespace Model {
enum class SlotID : uint8_t {
    PRIMARY_WEAPON = 0x00,
    SECONDARY_WEAPON = 0x01,
    KNIFE_SLOT = 0x02,
    BOMB_SLOT = 0x03
};
};

#endif  // COMMON_SLOT_ID_H
