#ifndef MATCH_CREATOR_H
#define MATCH_CREATOR_H

#include <cstdint>
#include <vector>

#include "common/DTO/drop_weapon_dto.h"
#include "common/DTO/match_dto.h"
#include "common/DTO/player_dto.h"

class MatchCreator {
private:
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

public:
    explicit MatchCreator(bool is_valid = false, uint8_t time_remaining = 0,
                          uint8_t round_number = 0, uint8_t ct_wins = 0, uint8_t tt_wins = 0,
                          const std::vector<PlayerDTO>& players = {},
                          const std::vector<DropWeaponDTO>& dropped_weapons = {},
                          uint8_t bomb_planted = 0, uint8_t bomb_defused = 0,
                          uint8_t bomb_exploded = 0, uint8_t winning_team = 0):
            is_valid(is_valid),
            time_remaining(time_remaining),
            round_number(round_number),
            ct_wins(ct_wins),
            tt_wins(tt_wins),
            players(players),
            dropped_weapons(dropped_weapons),
            bomb_planted(bomb_planted),
            bomb_defused(bomb_defused),
            bomb_exploded(bomb_exploded),
            winning_team(winning_team) {}

    DTO::MatchDTO to_dto() const;
};
#endif  // MATCH_CREATOR_H
