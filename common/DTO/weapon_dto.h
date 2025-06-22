#ifndef COMMON_DTO_WEAPON_DTO_H
#define COMMON_DTO_WEAPON_DTO_H

#include <cstdint>

#include "common/model/weapon.h"
#include "common/weapon_id.h"

namespace DTO {
struct WeaponDTO {
public:
    Model::WeaponID weapon_id;
    uint8_t loaded_ammo;
    uint16_t total_ammo;

    WeaponDTO(const WeaponDTO&) = default;

    WeaponDTO();

    WeaponDTO(Model::WeaponID weapon_id, uint8_t loaded_ammo, uint16_t total_ammo);

    Model::Weapon to_weapon() const;
};
}  // namespace DTO

#endif  // COMMON_DTO_WEAPON_DTO_H
