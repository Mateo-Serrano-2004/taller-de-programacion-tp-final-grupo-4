#include "common/DTO/round_dto.h"

DTO::RoundDTO::RoundDTO()
    : state(RoundState::Ended),
      ended(true),
      time_left(0),
      winner(Model::TeamID::NONE),
      bomb_planted(false),
      bomb_defused(false),
      bomb_position(0.0f, 0.0f),
      defusing_progress(0) {}

DTO::RoundDTO::RoundDTO(RoundState state, bool ended, uint16_t time_left, Model::TeamID winner, bool bomb_planted, bool bomb_defused, Physics::Vector2D bomb_position, uint8_t defusing_progress)
    : state(state), ended(ended), time_left(time_left), winner(winner), bomb_planted(bomb_planted), bomb_defused(bomb_defused), bomb_position(bomb_position), defusing_progress(defusing_progress)  {}
