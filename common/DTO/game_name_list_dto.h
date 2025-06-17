#ifndef COMMON_DTO_GAME_LIST_DTO_H
#define COMMON_DTO_GAME_LIST_DTO_H

#include <vector>
#include <string>

#include "common/definitions.h"

namespace DTO {
struct GameListDTO {
public:
    std::vector<std::string> maps_names;

    GameListDTO(std::vector<std::string> maps_names) : maps_names(maps_names) {}
};
};

#endif // COMMON_DTO_GAME_LIST_DTO_H
