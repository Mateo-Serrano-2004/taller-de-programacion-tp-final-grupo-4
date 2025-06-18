#ifndef COMMON_DTO_ROUND_DTO_H
#define COMMON_DTO_ROUND_DTO_H

#include <cstdint>

#include "common/round_state.h"
#include "common/team.h"

namespace DTO {
struct RoundDTO {
public:
    RoundState state;
    bool ended;
    uint16_t time_left;
    Model::TeamID winner;

    RoundDTO();
    RoundDTO(RoundState state, bool ended, uint16_t time_left, Model::TeamID winner);
};
}  // namespace DTO

#endif  // COMMON_DTO_ROUND_DTO_H
