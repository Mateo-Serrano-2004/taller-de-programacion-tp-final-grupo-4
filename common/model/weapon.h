#ifndef COMMON_MODEL_WEAPON_H
#define COMMON_MODEL_WEAPON_H

#include <cstdint>

#include "common/slot_id.h"
#include "common/weapon_id.h"

namespace DTO {
class WeaponDTO;
};

namespace Model {
class Weapon {
private:
    Model::WeaponID weapon_id;
    uint8_t loaded_ammo;
    uint16_t total_ammo;

public:
    Weapon(Model::WeaponID weapon_id, uint8_t loaded_ammo, uint16_t total_ammo);

    Model::WeaponID get_weapon_id() const;
    uint8_t get_loaded_ammo() const;
    uint16_t get_total_ammo() const;

    void set_weapon_id(Model::WeaponID new_weapon_id);
    void set_loaded_ammo(uint8_t new_loaded_ammo);
    void set_total_ammo(uint16_t new_total_ammo);

    Weapon(const Weapon&) = default;
    Weapon& operator=(const Weapon&) = default;
    Weapon(Weapon&&) = default;
    Weapon& operator=(Weapon&&) = default;

    DTO::WeaponDTO to_dto() const;

    virtual ~Weapon() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_WEAPON_H
