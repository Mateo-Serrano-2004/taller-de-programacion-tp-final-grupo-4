#include "game_state_dto.h"

#include <utility>

DTO::GameStateDTO::GameStateDTO():
        is_valid(false), ended(true), time_left(0) {}

DTO::GameStateDTO::GameStateDTO(bool is_valid, const std::vector<PlayerDTO>& players, bool ended, uint16_t time_left):
        is_valid(is_valid), players(std::move(players)), ended(ended), time_left(time_left) {}
