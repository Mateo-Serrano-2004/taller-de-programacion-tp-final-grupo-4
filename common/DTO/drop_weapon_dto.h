#ifndef DROP_WEAPON_DTO_H
#define DROP_WEAPON_DTO_H

#include <cstdint>
#include "weapon_dto.h"

namespace DTO {
struct DropWeaponDTO {
    uint8_t weapon_id;
    uint16_t position_x;
    uint16_t position_y;

    DropWeaponDTO();
    DropWeaponDTO(uint8_t weapon_id, uint16_t pos_x, uint16_t pos_y);
};
}  // namespace DTO

#endif  // DROP_WEAPON_DTO_H
