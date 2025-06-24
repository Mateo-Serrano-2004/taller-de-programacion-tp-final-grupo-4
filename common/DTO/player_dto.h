#ifndef PLAYER_DTO_H
#define PLAYER_DTO_H

#include <cstdint>
#include <string>

#include "common/definitions.h"
#include "common/model/player.h"

#include "weapon_dto.h"

namespace DTO {
struct PlayerDTO {
public:
    short_id_t player_id;
    short_id_t role_id;
    angle_t angle;
    uint16_t money;
    coord_t position_x;
    coord_t position_y;
    std::string name;
    uint8_t shooting;
    uint8_t defusing_bomb;
    uint8_t reloading;
    uint8_t health;
    short_id_t team;
    uint8_t deaths;
    uint8_t kills;
    uint8_t planting_progress;
    uint8_t has_bomb;
    uint8_t has_hit;

    WeaponDTO weapon_dto;

    PlayerDTO();

    PlayerDTO(short_id_t player_id, short_id_t role_id, angle_t angle, uint16_t money,
              coord_t position_x, coord_t position_y, const std::string& name,
              const DTO::WeaponDTO& weapon_dto, uint8_t shooting, uint8_t defusing_bomb,
              uint8_t reloading, uint8_t health, short_id_t team, uint8_t deaths, uint8_t kills,
              uint8_t planting_progress, uint8_t has_bomb, uint8_t has_hit);

    Model::Player to_player() const;
};
};  // namespace DTO

#endif  // PLAYER_DTO_H
