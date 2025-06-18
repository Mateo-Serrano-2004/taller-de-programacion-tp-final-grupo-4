#include "common/DTO/game_state_dto.h"

#include <utility>

DTO::GameStateDTO::GameStateDTO():
        game_state(GameState::Finished),
        ended(true),
        winner(Model::TeamID::NONE),
        ct_rounds_won(0),
        tt_rounds_won(0) {}

DTO::GameStateDTO::GameStateDTO(GameState game_state, const std::vector<PlayerDTO>& players,
                                bool ended, Model::TeamID winner, const DTO::RoundDTO& round,
                                uint8_t ct_rounds_won, uint8_t tt_rounds_won):
        game_state(game_state),
        players(std::move(players)),
        ended(ended),
        winner(winner),
        round(round),
        ct_rounds_won(ct_rounds_won),
        tt_rounds_won(tt_rounds_won) {}
