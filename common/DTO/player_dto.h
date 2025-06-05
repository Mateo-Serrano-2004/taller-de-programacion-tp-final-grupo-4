#ifndef PLAYER_DTO_H
#define PLAYER_DTO_H

#include <string>

#include "common/definitions.h"

#include "weapon_dto.h"

namespace DTO {
struct PlayerDTO {
public:
    short_id_t player_id;
    short_id_t skin_id;
    short_id_t skin_piece;
    angle_t angle;
    coord_t position_x;
    coord_t position_y;
    std::string name;

    WeaponDTO weapon_dto;

    PlayerDTO(short_id_t player_id, short_id_t skin_id, short_id_t skin_piece, angle_t angle,
              coord_t position_x, coord_t position_y, const std::string& name, const DTO::WeaponDTO& weapon_dto);
};
};  // namespace DTO

#endif  // PLAYER_DTO_H
