#ifndef COMMON_DTO_GAME_STATE_DTO_H
#define COMMON_DTO_GAME_STATE_DTO_H

#include <vector>

#include "common/DTO/player_dto.h"

namespace DTO {
struct GameStateDTO {
public:
    bool is_valid;
    std::vector<PlayerDTO> players;
    bool ended;
    uint16_t time_left;

    GameStateDTO();
    GameStateDTO(bool is_valid, const std::vector<PlayerDTO>& players, bool ended, uint16_t time_left);
};
};  // namespace DTO

#endif  // COMMON_DTO_GAME_STATE_DTO_H
