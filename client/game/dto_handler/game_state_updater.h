#ifndef CLIENT_DTO_PARSER_GAME_STATE_UPDATER_H
#define CLIENT_DTO_PARSER_GAME_STATE_UPDATER_H

#include <cstdint>

#include "common/definitions.h"
#include "common/DTO/match_dto.h"

#include "player_dto_parser.h"

namespace Model {
    class GameState;
}

namespace DTO {
    class GameStateUpdater {
    private:
        Model::GameState* game_state;
        PlayerDTOParser player_dto_parser;
        const uint8_t reference_player_id;

    public:
        GameStateUpdater(Model::GameState* game_state);

        void update(DTO::MatchDTO&& match_dto);

        ~GameStateUpdater() = default;
    };
};

#endif // CLIENT_DTO_PARSER_GAME_STATE_UPDATER_H
