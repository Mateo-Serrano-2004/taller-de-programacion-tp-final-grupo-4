#ifndef SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H
#define SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H

#include <cstdint>
#include "damage_mode.h"

struct WeaponShotInfo {
    uint8_t bullets_fired;         // Cantidad de proyectiles disparados por trigger (ej: 1 para Glock, 8 para M3)

    float base_damage;             // Daño máximo que puede infligir cada proyectil
    float min_damage;              // Daño mínimo por proyectil
    float max_range;               // Rango máximo de alcance del disparo

    float precision;               // Probabilidad base de acertar un blanco (0.0 a 1.0)
    float dispersion;              // Variación angular en radianes

    DamageMode damage_mode;        // Forma en que se calcula el daño con la distancia

    // Solo si damage_mode == LINEAR_FALLOFF o SHORT_RANGE_BOOST
    float falloff_factor;          // Pendiente de la caída lineal

    // Solo si damage_mode == SHORT_RANGE_BOOST
    float close_range_threshold;   // Distancia máxima donde se aplica el multiplicador de corto alcance
    float close_range_multiplier; // Factor multiplicador si se está dentro del rango corto (ej: daño * 1.8)

    // Constructor por defecto (opcional)
    WeaponShotInfo() = default;

    WeaponShotInfo(
        uint8_t bullets_fired,
        float base_damage,
        float min_damage,
        float max_range,
        float precision,
        float dispersion,
        DamageMode damage_mode,
        float falloff_factor = 0.0f,
        float close_range_threshold = 0.0f,
        float close_range_multiplier = 1.0f
    )
        : bullets_fired(bullets_fired),
          base_damage(base_damage),
          min_damage(min_damage),
          max_range(max_range),
          precision(precision),
          dispersion(dispersion),
          damage_mode(damage_mode),
          falloff_factor(falloff_factor),
          close_range_threshold(close_range_threshold),
          close_range_multiplier(close_range_multiplier) {}
};

#endif  // SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H
