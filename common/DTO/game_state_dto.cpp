#include "common/DTO/game_state_dto.h"

#include <utility>

DTO::GameStateDTO::GameStateDTO()
    : game_state(GameState::WaitingStart),
      ended(false),
      winner(Model::TeamID::NONE) {}

DTO::GameStateDTO::GameStateDTO(GameState game_state,
                                 const std::vector<PlayerDTO>& players,
                                 bool ended,
                                 Model::TeamID winner,
                                 const RoundDTO& round)
    : game_state(game_state),
      players(std::move(players)),
      ended(ended),
      winner(winner),
      round(round) {}
