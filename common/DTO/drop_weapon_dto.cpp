#include "drop_weapon_dto.h"

namespace DTO {

DropWeaponDTO::DropWeaponDTO() = default;

DropWeaponDTO::DropWeaponDTO(Model::WeaponID weapon_id, coord_t pos_x, coord_t pos_y):
        weapon_id(weapon_id), position_x(pos_x), position_y(pos_y) {}

}  // namespace DTO
