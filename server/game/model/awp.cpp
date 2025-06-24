#include "awp.h"

#include <algorithm>

#include "common/definitions.h"
#include "server/parser/yaml_parser.h"

AWP::AWP():
        FullWeapon(Model::WeaponID::AWP, Model::SlotID::PRIMARY_WEAPON,
                   YamlParser::getConfigData().weapons.at("awp").initialAmmo,
                   YamlParser::getConfigData().weapons.at("awp").initialAmmo,
                   YamlParser::getConfigData().weapons.at("awp").maxAmmo,
                   static_cast<uint16_t>(YamlParser::getConfigData().weapons.at("awp").reloadTime *
                                         GAME_FPS),
                   static_cast<uint16_t>(YamlParser::getConfigData().weapons.at("awp").reloadTime *
                                         GAME_FPS)),
        damage(YamlParser::getConfigData().weapons.at("awp").damagePerBullet),
        precision(YamlParser::getConfigData().weapons.at("awp").precision),
        range(YamlParser::getConfigData().weapons.at("awp").range * TILE_SIZE),
        bullets_per_shot(YamlParser::getConfigData().weapons.at("awp").bulletsPerShot),
        dispersion(YamlParser::getConfigData().weapons.at("awp").dispersion),
        falloff_factor(0.0f),
        close_range_threshold(0.0f),
        close_range_multiplier(1.0f),
        fire_rate(YamlParser::getConfigData().weapons.at("awp").fireRate * GAME_FPS),
        fire_rate_remaining(0) {}

std::optional<WeaponShotInfo> AWP::shoot(uint16_t ticks_to_process) {
    fire_rate_remaining = std::max(0, fire_rate_remaining - static_cast<int>(ticks_to_process));

    if (!triggered || trigger_blocked || get_loaded_ammo() == 0 || fire_rate_remaining > 0)
        return std::nullopt;

    set_loaded_ammo(get_loaded_ammo() - 1);
    trigger_blocked = true;
    fire_rate_remaining = fire_rate;

    return WeaponShotInfo(bullets_per_shot, damage, damage, range, precision, dispersion,
                          DamageMode::CONSTANT, falloff_factor, close_range_threshold,
                          close_range_multiplier);
}
