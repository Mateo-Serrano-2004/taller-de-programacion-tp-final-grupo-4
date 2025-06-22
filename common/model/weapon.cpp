#include "weapon.h"

#include "common/DTO/weapon_dto.h"
#include "common/definitions.h"
#include "common/weapon_id.h"

Model::Weapon::Weapon(Model::WeaponID weapon_id, uint8_t loaded_ammo, uint16_t total_ammo):
        weapon_id(weapon_id), loaded_ammo(loaded_ammo), total_ammo(total_ammo) {}

Model::WeaponID Model::Weapon::get_weapon_id() const { return weapon_id; }

uint8_t Model::Weapon::get_loaded_ammo() const { return loaded_ammo; }

uint16_t Model::Weapon::get_total_ammo() const { return total_ammo; }

void Model::Weapon::set_weapon_id(Model::WeaponID new_weapon_id) { weapon_id = new_weapon_id; }

void Model::Weapon::set_loaded_ammo(uint8_t new_loaded_ammo) { loaded_ammo = new_loaded_ammo; }

void Model::Weapon::set_total_ammo(uint16_t new_total_ammo) { total_ammo = new_total_ammo; }

DTO::WeaponDTO Model::Weapon::to_dto() const {
    return DTO::WeaponDTO(weapon_id, loaded_ammo, total_ammo);
}
