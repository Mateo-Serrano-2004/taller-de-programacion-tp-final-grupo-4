#ifndef SERVER_GAME_MODEL_SHOT_INFO_H
#define SERVER_GAME_MODEL_SHOT_INFO_H

#include "common/definitions.h"
#include "common/model/vector_2d.h"
#include "common/weapon_id.h"

#include "weapon_shot_info.h"

struct ShotInfo {
    short_id_t shooter_id;
    Physics::Vector2D origin;
    float angle;
    Model::WeaponID weapon_id;
    WeaponShotInfo weapon_info;

    ShotInfo(short_id_t shooter_id, const Physics::Vector2D& origin, float angle,
             Model::WeaponID weapon_id, const WeaponShotInfo& weapon_info):
            shooter_id(shooter_id),
            origin(origin),
            angle(angle),
            weapon_id(weapon_id),
            weapon_info(weapon_info) {}
};

#endif  // SERVER_GAME_MODEL_SHOT_INFO_H
