#ifndef CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H
#define CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H

#include "common/model/player.h"
#include "common/texture_id.h"
#include "common/weapon_type.h"

namespace DTO {
class PlayerDTO;

class PlayerDTOParser {
private:
    Model::TextureID get_texture_id(WeaponID weapon_id);

public:
    PlayerDTOParser() = default;

    Model::Player parse(PlayerDTO&& player_dto);

    ~PlayerDTOParser() = default;
};
};  // namespace DTO

#endif  // CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H
