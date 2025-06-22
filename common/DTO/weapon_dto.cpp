#include "weapon_dto.h"

#include "common/weapon_id.h"

DTO::WeaponDTO::WeaponDTO(): weapon_id(Model::WeaponID::KNIFE), loaded_ammo(0), total_ammo(0) {}

DTO::WeaponDTO::WeaponDTO(Model::WeaponID weapon_id, uint8_t loaded_ammo, uint16_t total_ammo):
        weapon_id(weapon_id), loaded_ammo(loaded_ammo), total_ammo(total_ammo) {}

Model::Weapon DTO::WeaponDTO::to_weapon() const {
    return Model::Weapon(weapon_id, loaded_ammo, total_ammo);
}
