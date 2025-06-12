#include "common/DTO/round_dto.h"

DTO::RoundDTO::RoundDTO()
    : state(RoundState::Ended), ended(true), time_left(0), winner(Model::TeamID::NONE) {}

DTO::RoundDTO::RoundDTO(RoundState state, bool ended, uint16_t time_left, Model::TeamID winner)
    : state(state), ended(ended), time_left(time_left), winner(winner) {}
