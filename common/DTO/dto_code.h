#ifndef COMMON_DTO_DTO_CODE_H
#define COMMON_DTO_DTO_CODE_H

#include <cstdint>

namespace DTO {
enum class DTOCode : uint8_t {
    GAME_STATE = 0x00,
    PLAYER_ID = 0x01,
    TEAM_ID = 0x02,
    MAP = 0x03,
    MAP_NAMES_LIST = 0x04,
    GAMES_LIST = 0x05,
    CONFIG = 0x06
};
};

#endif  // COMMON_DTO_DTO_CODE_H
