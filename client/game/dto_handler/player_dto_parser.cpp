#include "player_dto_parser.h"

#include "common/model/vector_2d.h"

Model::Player DTO::PlayerDTOParser::parse(DTO::PlayerDTO& player_dto) {
    return Model::Player(player_dto.player_id, player_dto.skin_id, player_dto.skin_piece,
                         player_dto.angle, player_dto.name,
                         Physics::Vector2D(player_dto.position_x, player_dto.position_y));
}
