#ifndef SERVER_GAME_MODEL_FULL_WEAPON_H
#define SERVER_GAME_MODEL_FULL_WEAPON_H

#include <algorithm>
#include <optional>

#include "common/model/weapon.h"
#include "common/slot_id.h"
#include "common/weapon_id.h"

#include "weapon_shot_info.h"

class FullWeapon: public Model::Weapon {
protected:
    Model::SlotID slot_id;
    bool triggered = false;
    bool trigger_blocked = false;
    bool reloading = false;
    uint16_t ticks_to_reload;
    uint16_t ticks_remaining_to_reload;
    uint8_t max_loaded_ammo;

    virtual void stop_reloading();

public:
    FullWeapon(Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo,
               uint8_t max_loaded_ammo, uint16_t total_ammo, uint16_t ticks_to_reload,
               uint16_t ticks_remaining_to_reload);

    Model::SlotID get_slot_id() const;

    virtual void press_trigger();
    virtual void release_trigger();
    virtual void start_reloading();
    virtual void add_ammo();

    virtual std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) = 0;
    virtual bool reload(uint16_t ticks_to_process);

    virtual ~FullWeapon() = default;
};

#endif  // SERVER_GAME_MODEL_FULL_WEAPON_H
