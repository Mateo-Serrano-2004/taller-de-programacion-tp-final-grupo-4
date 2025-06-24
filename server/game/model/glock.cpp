#include "glock.h"

#include <algorithm>

#include "common/definitions.h"
#include "server/parser/yaml_parser.h"

Glock::Glock():
        FullWeapon(Model::WeaponID::GLOCK, Model::SlotID::SECONDARY_WEAPON,
                   YamlParser::getConfigData().weapons.at("glock").initialAmmo,
                   YamlParser::getConfigData().weapons.at("glock").initialAmmo,
                   YamlParser::getConfigData().weapons.at("glock").maxAmmo,
                   static_cast<uint16_t>(
                           YamlParser::getConfigData().weapons.at("glock").reloadTime * GAME_FPS),
                   static_cast<uint16_t>(
                           YamlParser::getConfigData().weapons.at("glock").reloadTime * GAME_FPS)),
        damage(YamlParser::getConfigData().weapons.at("glock").damagePerBullet),
        precision(YamlParser::getConfigData().weapons.at("glock").precision),
        range(YamlParser::getConfigData().weapons.at("glock").range * TILE_SIZE),
        bullets_per_shot(YamlParser::getConfigData().weapons.at("glock").bulletsPerShot),
        dispersion(YamlParser::getConfigData().weapons.at("glock").dispersion),
        falloff_factor(0.05f),
        close_range_threshold(0.0f),
        close_range_multiplier(1.0f),
        fire_rate(YamlParser::getConfigData().weapons.at("glock").fireRate * GAME_FPS),
        fire_rate_remaining(0) {
    if (range == 0) {
        min_damage = 0;
    } else {
        min_damage = damage / (range / TILE_SIZE);
    }
}

std::optional<WeaponShotInfo> Glock::shoot(uint16_t ticks_to_process) {
    fire_rate_remaining = std::max(0, fire_rate_remaining - static_cast<int>(ticks_to_process));

    if (!triggered || trigger_blocked || get_loaded_ammo() == 0 || fire_rate_remaining > 0)
        return std::nullopt;

    set_loaded_ammo(get_loaded_ammo() - 1);
    trigger_blocked = true;
    fire_rate_remaining = fire_rate;

    return WeaponShotInfo(bullets_per_shot, damage, min_damage, range, precision, dispersion,
                          DamageMode::LINEAR_FALLOFF, falloff_factor, close_range_threshold,
                          close_range_multiplier);
}
