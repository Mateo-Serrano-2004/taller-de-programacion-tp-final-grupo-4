#include "weapon_dto.h"

DTO::WeaponDTO::WeaponDTO(): weapon_id(0), loaded_ammo(0), total_ammo(0) {}

DTO::WeaponDTO::WeaponDTO(uint8_t weapon_id, uint8_t loaded_ammo, uint8_t total_ammo):
        weapon_id(weapon_id), loaded_ammo(loaded_ammo), total_ammo(total_ammo) {}
