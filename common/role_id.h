#ifndef COMMON_ROLE_ID_H
#define COMMON_ROLE_ID_H

#include <cstdint>

namespace Model {
enum class RoleID : uint8_t {
    CT1 = 0x00,
    CT2 = 0x01,
    CT3 = 0x02,
    CT4 = 0x03,
    T1 = 0x04,
    T2 = 0x05,
    T3 = 0x06,
    T4 = 0x07,
    NO_ROLE = 0x08
};
};

#endif  // COMMON_ROLE_ID_H
