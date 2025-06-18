#ifndef TEAM_H
#define TEAM_H

#include <cstdint>

namespace Model {
enum class TeamID : uint8_t {
    CT = 0x00,
    TT = 0x01,
    NONE = 0x02,
};
};
#endif  // TEAM_H
