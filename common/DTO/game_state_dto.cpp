#include "game_state_dto.h"

DTO::GameStateDTO::GameStateDTO() : is_valid(false) {}

DTO::GameStateDTO::GameStateDTO(bool is_valid, const std::vector<PlayerDTO>& players):
        is_valid(is_valid), players(std::move(players)) {}
