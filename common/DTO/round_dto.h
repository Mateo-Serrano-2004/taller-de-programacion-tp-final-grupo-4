#ifndef COMMON_DTO_ROUND_DTO_H
#define COMMON_DTO_ROUND_DTO_H

#include <vector>
#include <cstdint>

#include "common/model/vector_2d.h"
#include "common/round_state.h"
#include "common/team.h"
#include "common/DTO/drop_weapon_dto.h"

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
    uint8_t defusing_progress;
    std::vector<DTO::DropWeaponDTO> dropped_weapons;

    RoundDTO();
    RoundDTO(RoundState state, bool ended, uint16_t time_left, Model::TeamID winner,
             bool bomb_planted, bool bomb_defused, Physics::Vector2D bomb_position,
             uint8_t defusing_progress, const std::vector<DTO::DropWeaponDTO>& dropped_weapons);
};
}  // namespace DTO

#endif  // COMMON_DTO_ROUND_DTO_H
