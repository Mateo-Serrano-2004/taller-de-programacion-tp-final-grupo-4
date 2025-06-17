#ifndef SERVER_GAME_MODEL_WEAPONS_AK47_H
#define SERVER_GAME_MODEL_WEAPONS_AK47_H

#include "full_weapon.h"
#include "weapon_shot_info.h"

class AK47 : public FullWeapon {
private:
    bool in_burst = false;
    uint8_t bullets_in_current_burst = 0;
    uint16_t ticks_until_next_bullet = 0;
    static constexpr uint16_t ticks_between_burst_bullets = 24; // 0.4s a 60 FPS
    static constexpr uint16_t burst_cooldown_ticks = 48;        // 0.8s a 60 FPS
    
public:
    AK47();
    void press_trigger() override;
    void release_trigger() override;
    std::optional<WeaponShotInfo> shoot(uint16_t ticks_to_process) override;
};
    
#endif // SERVER_GAME_MODEL_WEAPONS_AK47_H