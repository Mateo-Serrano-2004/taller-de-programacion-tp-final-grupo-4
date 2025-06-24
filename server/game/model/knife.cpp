#include "knife.h"

#include <algorithm>

#include "common/definitions.h"
#include "server/parser/yaml_parser.h"

Knife::Knife():
        FullWeapon(Model::WeaponID::KNIFE, Model::SlotID::KNIFE_SLOT, 1, 1, 1, 1, 1),
        damage(YamlParser::getConfigData().weapons.at("knife").damagePerBullet),
        precision(YamlParser::getConfigData().weapons.at("knife").precision),
        range(YamlParser::getConfigData().weapons.at("knife").range * TILE_SIZE),
        bullets_per_shot(YamlParser::getConfigData().weapons.at("knife").bulletsPerShot),
        dispersion(YamlParser::getConfigData().weapons.at("knife").dispersion),
        falloff_factor(0.0f),
        close_range_threshold(0.0f),
        close_range_multiplier(1.0f),
        fire_rate(YamlParser::getConfigData().weapons.at("knife").fireRate * GAME_FPS),
        fire_rate_remaining(0) {}

std::optional<WeaponShotInfo> Knife::shoot(uint16_t ticks_to_process) {
    fire_rate_remaining = std::max(0, fire_rate_remaining - static_cast<int>(ticks_to_process));

    if (!triggered || trigger_blocked || fire_rate_remaining > 0)
        return std::nullopt;

    trigger_blocked = true;
    fire_rate_remaining = fire_rate;

    return WeaponShotInfo(bullets_per_shot, damage, damage, range, precision, dispersion,
                          DamageMode::CONSTANT, falloff_factor, close_range_threshold,
                          close_range_multiplier);
}

bool Knife::reload(uint16_t) { return false; }

void Knife::add_ammo() {}
