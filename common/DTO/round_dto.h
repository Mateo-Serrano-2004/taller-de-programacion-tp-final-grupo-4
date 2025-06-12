#ifndef COMMON_DTO_ROUND_DTO_H
#define COMMON_DTO_ROUND_DTO_H

#include <cstdint>
#include "common/round_state.h"
#include "common/team.h"

namespace DTO {
struct RoundDTO {
public:
    RoundState state;      // Warmup, Buying, Active, Ended
    bool ended;
    uint16_t time_left;
    Model::TeamID winner;    // En segundos

    RoundDTO();  // default
    RoundDTO(RoundState state, bool ended, uint16_t time_left,Model::TeamID winner );
};
} 

#endif  // COMMON_DTO_ROUND_DTO_H
