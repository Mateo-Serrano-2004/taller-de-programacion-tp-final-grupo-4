#ifndef COMMON_DTO_GAME_LIST_DTO_H
#define COMMON_DTO_GAME_LIST_DTO_H

#include <string>
#include <vector>

#include "common/definitions.h"

#include "game_info_dto.h"

namespace DTO {
struct GameListDTO {
public:
    std::vector<GameInfoDTO> games;

    GameListDTO() = default;
    explicit GameListDTO(const std::vector<GameInfoDTO>& games): games(games) {}
};
};  // namespace DTO

#endif  // COMMON_DTO_GAME_LIST_DTO_H
