#ifndef SERVER_GAME_MODEL_FULL_WEAPON_H
#define SERVER_GAME_MODEL_FULL_WEAPON_H
#include <optional>

#include "common/model/weapon.h"
#include "common/slot_id.h"
#include "common/weapon_id.h"

#include "weapon_shot_info.h"

class FullWeapon: public Model::Weapon {
protected:
    Model::SlotID slot_id;
    bool triggered;
    bool trigger_blocked;
    bool automatic;
    uint16_t cooldown_ticks;
    uint16_t ticks_remaining = 0;

public:
    FullWeapon(Model::WeaponID weapon_id, Model::SlotID slot_id, uint8_t loaded_ammo,
               uint16_t total_ammo, bool automatic, uint16_t cooldown_ticks);

    Model::SlotID get_slot_id() const;

    void set_slot_id(Model::SlotID new_slot_id);
    void press_trigger();
    void release_trigger();
    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process);

    ~FullWeapon() override = default;
};

#endif  // SERVER_GAME_MODEL_FULL_WEAPON_H
