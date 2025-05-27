#include "../include/match_creator.h"

DTO::MatchDTO MatchCreator::to_dto() const {
    DTO::MatchDTO dto;
    dto.is_valid = is_valid;
    dto.time_remaining = time_remaining;
    dto.round_number = round_number;
    dto.ct_wins = ct_wins;
    dto.tt_wins = tt_wins;
    dto.players = players;
    dto.dropped_weapons = dropped_weapons;
    dto.bomb_planted = bomb_planted;
    dto.bomb_defused = bomb_defused;
    dto.bomb_exploded = bomb_exploded;
    dto.winning_team = winning_team;
    return dto;
}
