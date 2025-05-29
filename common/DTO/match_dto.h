#ifndef COMMON_DTO_MATCH_DTO_H
#define COMMON_DTO_MATCH_DTO_H

#include <vector>

#include "drop_weapon_dto.h"
#include "player_dto.h"

namespace DTO {
struct MatchDTO {
    bool is_valid;
    uint8_t time_remaining;
    uint8_t round_number;
    uint8_t ct_wins;
    uint8_t tt_wins;
    std::vector<PlayerDTO> players;
    std::vector<DropWeaponDTO> dropped_weapons;
    uint8_t bomb_planted;
    uint8_t bomb_defused;
    uint8_t bomb_exploded;
    uint8_t winning_team;
};
};  // namespace DTO

#endif  // COMMON_DTO_MATCH_DTO_H
