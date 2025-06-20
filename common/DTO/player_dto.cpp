#include "player_dto.h"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "common/role_id.h"

DTO::PlayerDTO::PlayerDTO():
        player_id(0),
        role_id(0),
        angle(0),
        money(0),
        position_x(0),
        position_y(0),
        shooting(0),
        defusing_bomb(0),
        reloading(0),
        health(0),
        team(0) {}

DTO::PlayerDTO::PlayerDTO(short_id_t player_id, short_id_t role_id, angle_t angle, uint16_t money,
                          coord_t position_x, coord_t position_y, const std::string& name,
                          const DTO::WeaponDTO& weapon_dto, uint8_t shooting, uint8_t defusing_bomb,
                          uint8_t reloading, uint8_t health, short_id_t team):
        player_id(player_id),
        role_id(role_id),
        angle(angle),
        money(money),
        position_x(position_x),
        position_y(position_y),
        name(name),
        weapon_dto(weapon_dto),
        shooting(shooting),
        defusing_bomb(defusing_bomb),
        reloading(reloading),
        health(health),
        team(team) {}

Model::Player DTO::PlayerDTO::to_player() const {
    return Model::Player(shooting, defusing_bomb, reloading, player_id, (Model::RoleID)(role_id),
                         angle, money, name, Physics::Vector2D(position_x, position_y),
                         make_shared<Model::Weapon>(std::move(weapon_dto.to_weapon())), health,
                         (Model::TeamID)(team));
}
