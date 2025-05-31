#ifndef CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H
#define CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H

#include "common/model/player.h"

namespace DTO {
class PlayerDTO;

class PlayerDTOParser {
private:
public:
    PlayerDTOParser() = default;

    Model::Player parse(PlayerDTO&& player_dto);

    ~PlayerDTOParser() = default;
};
};  // namespace DTO

#endif  // CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H
