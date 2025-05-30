#include "player_dto.h"

#include <string>

DTO::PlayerDTO::PlayerDTO(
    short_id_t player_id,
    short_id_t skin_id,
    short_id_t skin_piece,
    angle_t angle,
    coord_t position_x,
    coord_t position_y,
    std::string name
): player_id(player_id),
   skin_id(skin_id),
   skin_piece(skin_piece),
   angle(angle),
   position_x(position_x),
   position_y(position_y),
   name(std::move(name)) {}
