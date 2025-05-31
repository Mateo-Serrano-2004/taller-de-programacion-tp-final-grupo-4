#include "game_state_dto.h"

#include <utility>

DTO::GameStateDTO::GameStateDTO(): is_valid(false) {}

DTO::GameStateDTO::GameStateDTO(bool is_valid, const std::vector<PlayerDTO>& players, bool ended):
        is_valid(is_valid), players(std::move(players)), ended(ended) {}
