#ifndef COMMON_DTO_DTO_VARIANT_H
#define COMMON_DTO_DTO_VARIANT_H

#include <variant>

#include "config_dto.h"
#include "game_list_dto.h"
#include "game_state_dto.h"
#include "map_dto.h"
#include "map_name_list_dto.h"
#include "player_id_dto.h"
#include "team_id_dto.h"

namespace DTO {
using DTOVariant = std::variant<GameStateDTO, PlayerIDDTO, TeamIDDTO, MapDTO, MapNameListDTO,
                                GameListDTO, ConfigDTO>;
};

#endif  // COMMON_DTO_DTO_VARIANT_H
