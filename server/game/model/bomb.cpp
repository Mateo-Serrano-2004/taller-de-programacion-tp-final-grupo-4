#include "bomb.h"

Bomb::Bomb()
    : FullWeapon(
        Model::WeaponID::BOMB,
        Model::SlotID::BOMB_SLOT,
        1, // loaded_ammo
        1, // total_ammo (no se recarga)
        0,
        0  
    )
{}

void Bomb::press_trigger() {
    if (!planted)
        is_planting = true;
}

void Bomb::release_trigger() {
    is_planting = false;
    planting_ticks = 0;
}

std::optional<WeaponShotInfo> Bomb::shoot(uint16_t ticks_to_process) {
    if (planted || !is_planting)
        return std::nullopt;

    planting_ticks += ticks_to_process;

    if (planting_ticks >= required_ticks_to_plant) {
        planted = true;

        return WeaponShotInfo(0,     // no balas
                              0.0f,  // sin daño
                              0.0f, 0.0f, 0.0f, 0.0f, DamageMode::CONSTANT, 0.0f, 0.0f, 1.0f);
    }

    return std::nullopt;
}

bool Bomb::is_planted() const {
    return planted;
}

bool Bomb::reload(uint16_t ticks_to_process) {
    return false;
}