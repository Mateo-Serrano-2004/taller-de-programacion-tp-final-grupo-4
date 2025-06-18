#ifndef DROP_WEAPON_DTO_H
#define DROP_WEAPON_DTO_H

#include <cstdint>

#include "weapon_dto.h"

namespace DTO {
struct DropWeaponDTO {
    WeaponDTO weapon;
    uint16_t position_x;
    uint16_t position_y;

    DropWeaponDTO();
};
}  // namespace DTO

#endif  // DROP_WEAPON_DTO_H
