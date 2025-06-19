#ifndef SERVER_GAME_MODEL_FULL_WEAPON_H
#define SERVER_GAME_MODEL_FULL_WEAPON_H
#include <iostream>

#include <optional>

#include "common/model/weapon.h"
#include "common/slot_id.h"
#include "common/weapon_id.h"

#include "weapon_shot_info.h"

class FullWeapon : public Model::Weapon {
protected:
    Model::SlotID slot_id;
    bool triggered = false;
    bool trigger_blocked = false;

public:
    FullWeapon(Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo, uint16_t total_ammo);

    Model::SlotID get_slot_id() const;

    virtual void press_trigger();
    virtual void release_trigger();

    virtual std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) = 0;

    virtual ~FullWeapon() = default;
};

#endif  // SERVER_GAME_MODEL_FULL_WEAPON_H
