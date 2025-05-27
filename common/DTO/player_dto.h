#ifndef PLAYER_DTO_H
#define PLAYER_DTO_H

#include <cstdint>
#include <string>

#include "weapon_dto.h"

struct PlayerDTO {
    std::string name;
    uint8_t player_id;
    uint8_t skin_id;
    WeaponDTO current_weapon;
    uint8_t has_bomb;
    uint8_t health;
    uint16_t money;
    uint16_t position_x;
    uint16_t position_y;
    uint16_t angle;
};

#endif  // PLAYER_DTO_H
