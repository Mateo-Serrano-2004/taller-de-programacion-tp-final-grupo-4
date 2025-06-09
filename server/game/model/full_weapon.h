#ifndef SERVER_GAME_MODEL_FULL_WEAPON_H
#define SERVER_GAME_MODEL_FULL_WEAPON_H

#include "common/slot_id.h"
#include "common/weapon_id.h"
#include "common/model/weapon.h"

class FullWeapon: public Model::Weapon {
protected:
    Model::SlotID slot_id;

public:
    FullWeapon(Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo, uint16_t total_ammo);

    Model::SlotID get_slot_id() const;

    void set_slot_id(Model::SlotID new_slot_id);

    ~FullWeapon() override = default;
};

#endif // SERVER_GAME_MODEL_FULL_WEAPON_H
