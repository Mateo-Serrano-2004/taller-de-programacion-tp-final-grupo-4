#include "drop_weapon_dto.h"

namespace DTO {

DropWeaponDTO::DropWeaponDTO() = default;

DropWeaponDTO::DropWeaponDTO(uint8_t weapon_id, uint16_t pos_x, uint16_t pos_y)
    : weapon_id(weapon_id), position_x(pos_x), position_y(pos_y) {}

}
