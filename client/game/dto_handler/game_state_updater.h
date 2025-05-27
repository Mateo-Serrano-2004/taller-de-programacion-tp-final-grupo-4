#ifndef CLIENT_DTO_PARSER_GAME_STATE_UPDATER_H
#define CLIENT_DTO_PARSER_GAME_STATE_UPDATER_H

#include <cstdint>

#include "common/definitions.h"

namespace Model {
    class GameState;
}

namespace DTO {
    class GameStateUpdater {
    private:
        Model::GameState* game_state;
        const uint8_t reference_player_id;

    public:
        GameStateUpdater(Model::GameState* game_state);

        Shared<Model::GameState> parse(MatchDTO&& match_dto);

        ~GameStateUpdater() = default;
    }
};

#endif // CLIENT_DTO_PARSER_GAME_STATE_UPDATER_H
