#include "player_dto_parser.h"

Model::Player DTO::PlayerDTOParser::parse(PlayerDTO& player_dto) {
    return Model::Player(
        player_dto.player_id,
        player_dto.position_x,
        player_dto.position_y,
        player_dto.angle,
        player_dto.skin_id
    );
}
