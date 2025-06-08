#include "weapon.h"

#include "common/texture_id.h"

Model::Weapon::Weapon(): sprite_id(0), ammo_in_charger(0), total_ammo(0) {}

Model::Weapon::Weapon(uint8_t sprite_id, uint8_t ammo_in_charger, uint16_t total_ammo):
        sprite_id(sprite_id), ammo_in_charger(ammo_in_charger), total_ammo(total_ammo) {}

uint8_t Model::Weapon::get_sprite_id() const { return sprite_id; }

uint8_t Model::Weapon::get_ammo_in_charger() const { return ammo_in_charger; }

uint16_t Model::Weapon::get_total_ammo() const { return total_ammo; }

void Model::Weapon::set_sprite_id(uint8_t new_sprite_id) {
    sprite_id = new_sprite_id;
}

void Model::Weapon::set_ammo_in_charger(uint8_t new_ammo_in_charger) {
    ammo_in_charger = new_ammo_in_charger;
}

void Model::Weapon::set_total_ammo(uint16_t new_total_ammo) {
    total_ammo = new_total_ammo;
}

DTO::WeaponDTO Model::Weapon::to_dto() const {
    return DTO::WeaponDTO(
        sprite_id,
        ammo_in_charger,
        total_ammo
    );
}
