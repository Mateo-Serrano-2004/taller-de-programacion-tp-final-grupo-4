#ifndef DROP_WEAPON_DTO_H
#define DROP_WEAPON_DTO_H

#include <cstdint>

#include "common/definitions.h"
#include "common/weapon_id.h"

namespace DTO {
struct DropWeaponDTO {
    Model::WeaponID weapon_id;
    coord_t position_x;
    coord_t position_y;

    DropWeaponDTO();
    DropWeaponDTO(Model::WeaponID weapon_id, coord_t pos_x, coord_t pos_y);
};
}  // namespace DTO

#endif  // DROP_WEAPON_DTO_H
