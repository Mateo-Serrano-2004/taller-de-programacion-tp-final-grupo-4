#include "weapon_dto.h"

DTO::WeaponDTO::WeaponDTO(uint8_t sprite_id, uint8_t loaded_ammo, uint16_t total_ammo)
: sprite_id(sprite_id), loaded_ammo(loaded_ammo), total_ammo(total_ammo) {}
