#include "ak47.h"

#include "common/definitions.h"
#include "server/parser/yaml_parser.h"

AK47::AK47():
        FullWeapon(Model::WeaponID::AK47, Model::SlotID::PRIMARY_WEAPON,
                   YamlParser::getConfigData().weapons.at("ak-47").initialAmmo,
                   YamlParser::getConfigData().weapons.at("ak-47").initialAmmo,
                   YamlParser::getConfigData().weapons.at("ak-47").maxAmmo,
                   static_cast<uint16_t>(
                           YamlParser::getConfigData().weapons.at("ak-47").reloadTime * GAME_FPS),
                   static_cast<uint16_t>(
                           YamlParser::getConfigData().weapons.at("ak-47").reloadTime * GAME_FPS)),
        damage(YamlParser::getConfigData().weapons.at("ak-47").damagePerBullet),
        precision(YamlParser::getConfigData().weapons.at("ak-47").precision),
        range(YamlParser::getConfigData().weapons.at("ak-47").range * TILE_SIZE),
        bullets_per_shot(YamlParser::getConfigData().weapons.at("ak-47").bulletsPerShot),
        dispersion(YamlParser::getConfigData().weapons.at("ak-47").dispersion),
        falloff_factor(0.05f),
        close_range_threshold(0.0f),
        close_range_multiplier(1.0f),
        fire_rate(YamlParser::getConfigData().weapons.at("ak-47").fireRate * GAME_FPS),
        fire_rate_remaining(0),
        in_burst(false),
        bullets_in_current_burst(0),
        ticks_until_next_bullet(0),
        ticks_between_burst_bullets(0.4 * GAME_FPS),
        burst_cooldown_ticks(0.8 * GAME_FPS) {
    if (range == 0) {
        min_damage = 0;
    } else {
        min_damage = damage / (range / TILE_SIZE);
    }
}

void AK47::press_trigger() {
    triggered = true;
    if (!in_burst && get_loaded_ammo() > 0) {
        in_burst = true;
        bullets_in_current_burst = 0;
        ticks_until_next_bullet = 0;
    }
}

void AK47::release_trigger() {
    triggered = false;
    trigger_blocked = false;
    in_burst = false;
    bullets_in_current_burst = 0;
    ticks_until_next_bullet = 0;
}

std::optional<WeaponShotInfo> AK47::shoot(uint16_t ticks_to_process) {
    if (!triggered)
        return std::nullopt;

    if (!in_burst) {
        if (ticks_until_next_bullet > ticks_to_process) {
            ticks_until_next_bullet -= ticks_to_process;
            return std::nullopt;
        }

        if (get_loaded_ammo() > 0) {
            in_burst = true;
            bullets_in_current_burst = 0;
            ticks_until_next_bullet = 0;
        } else {
            return std::nullopt;
        }
    }

    if (ticks_until_next_bullet > ticks_to_process) {
        ticks_until_next_bullet -= ticks_to_process;
        return std::nullopt;
    }

    if (bullets_in_current_burst >= 3) {
        in_burst = false;
        ticks_until_next_bullet = burst_cooldown_ticks;
        return std::nullopt;
    }

    if (get_loaded_ammo() == 0) {
        in_burst = false;
        return std::nullopt;
    }

    set_loaded_ammo(get_loaded_ammo() - 1);
    bullets_in_current_burst++;
    ticks_until_next_bullet = ticks_between_burst_bullets;

    return WeaponShotInfo(bullets_per_shot, damage, min_damage, range, precision, dispersion,
                          DamageMode::LINEAR_FALLOFF, falloff_factor, close_range_threshold,
                          close_range_multiplier);
}
