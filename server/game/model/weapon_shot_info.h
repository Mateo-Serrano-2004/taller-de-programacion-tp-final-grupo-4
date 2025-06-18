#ifndef SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H
#define SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H

#include <cstdint>

struct WeaponShotInfo {
    uint8_t bullets_fired;  // Cuántos proyectiles lanza (1 para Glock, 6-8 para escopeta)
    float max_damage;       // Daño máximo (distancia cero o ideal)
    float precision;        // Precisión base (0.0 a 1.0)
    float dispersion;       // Dispersión angular, en radianes
    float damage_falloff;   // Factor de caída de daño (por unidad de distancia)

    // Constructor explícito para comodidad
    WeaponShotInfo(uint8_t bullets_fired, float max_damage, float precision, float dispersion,
                   float damage_falloff):
            bullets_fired(bullets_fired),
            max_damage(max_damage),
            precision(precision),
            dispersion(dispersion),
            damage_falloff(damage_falloff) {}
};

#endif  // SERVER_GAME_MODEL_WEAPON_SHOT_INFO_H
