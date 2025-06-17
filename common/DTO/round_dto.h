#ifndef COMMON_DTO_ROUND_DTO_H
#define COMMON_DTO_ROUND_DTO_H

#include <cstdint>
#include "common/round_state.h"
#include "common/team.h"
#include "common/model/vector_2d.h" 

namespace DTO {
struct RoundDTO {
public:
    RoundState state;
    bool ended;
    uint16_t time_left;
    Model::TeamID winner;
    bool bomb_planted;
    bool bomb_defused;
    Physics::Vector2D bomb_position;

    RoundDTO();
    RoundDTO(
        RoundState state, 
        bool ended, 
        uint16_t time_left, 
        Model::TeamID winner,
        bool bomb_planted,
        bool bomb_defused,
        Physics::Vector2D bomb_position);
};
} 

#endif  // COMMON_DTO_ROUND_DTO_H
