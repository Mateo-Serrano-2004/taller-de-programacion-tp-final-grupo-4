#ifndef COMMON_DTO_GAME_STATE_DTO_H
#define COMMON_DTO_GAME_STATE_DTO_H

#include <vector>

#include "common/DTO/player_dto.h"
#include "common/DTO/round_dto.h"
#include "common/game_state.h"
#include "common/team.h"

namespace DTO {
struct GameStateDTO {
public:
    GameState game_state;
    std::vector<PlayerDTO> players;
    bool ended;
    Model::TeamID winner;
    RoundDTO round;
    uint8_t ct_rounds_won;
    uint8_t tt_rounds_won;

    GameStateDTO();
    GameStateDTO(GameState game_state, const std::vector<PlayerDTO>& players, bool ended,
                 Model::TeamID winner, const RoundDTO& round, uint8_t ct_rounds_won,
                 uint8_t tt_rounds_won);
};
}  // namespace DTO

#endif  // COMMON_DTO_GAME_STATE_DTO_H
