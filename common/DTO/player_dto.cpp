#include "player_dto.h"

#include <string>
#include <cstdint>
#include <memory>

#include "common/role_id.h"

DTO::PlayerDTO::PlayerDTO(short_id_t player_id, short_id_t role_id,
                          angle_t angle, uint16_t money,
                          coord_t position_x, coord_t position_y,
                          const std::string& name, const DTO::WeaponDTO& weapon_dto):
        player_id(player_id),
        role_id(role_id),
        angle(angle),
        money(money),
        position_x(position_x),
        position_y(position_y),
        name(name),
        weapon_dto(weapon_dto) {}

Model::Player DTO::PlayerDTO::to_player() const {
    return Model::Player(
        player_id, (Model::RoleID) (role_id), angle, money,
        name,
        Physics::Vector2D(position_x, position_y),
        make_shared<Model::Weapon>(std::move(weapon_dto.to_weapon()))
    );
}
