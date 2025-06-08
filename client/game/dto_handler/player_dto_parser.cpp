#include "player_dto_parser.h"

#include "common/model/vector_2d.h"
#include "common/model/weapon.h"
#include "common/DTO/player_dto.h"

Model::Player DTO::PlayerDTOParser::parse(DTO::PlayerDTO&& player_dto) {
    return Model::Player(player_dto.player_id, player_dto.skin_id, player_dto.skin_piece,
                         player_dto.angle, player_dto.name,
                         Physics::Vector2D(player_dto.position_x, player_dto.position_y),
                         Model::Weapon(
                            player_dto.weapon_dto.sprite_id,
                            player_dto.weapon_dto.loaded_ammo,
                            player_dto.weapon_dto.total_ammo
                        ));
}
