#ifndef CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H
#define CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H

#include "common/DTO/player_dto.h"
#include "model/player.h"

namespace DTO {
    class PlayerDTOParser {
    private:
    public:
        PlayerDTOParser() = default;

        Model::Player parse(PlayerDTO& player_dto);

        ~PlayerDTOParser() = default;
    };
};

#endif // CLIENT_GAME_DTO_HANDLER_PLAYER_DTO_PARSER_H
