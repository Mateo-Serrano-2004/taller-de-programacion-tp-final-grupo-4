#ifndef COMMON_DTO_GAME_LIST_DTO_H
#define COMMON_DTO_GAME_LIST_DTO_H

#include <vector>
#include <string>

#include "common/definitions.h"
#include "game_info_dto.h"

namespace DTO {
struct GameListDTO {
public:
    std::vector<GameInfoDTO> games;

    GameListDTO() = default;
    GameListDTO(const std::vector<GameInfoDTO>& games) : games(games) {}
};
};

#endif // COMMON_DTO_GAME_LIST_DTO_H
