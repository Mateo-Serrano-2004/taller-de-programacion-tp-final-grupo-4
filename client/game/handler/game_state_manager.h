#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <functional>
#include <mutex>

#include "common/definitions.h"
#include "model/game_state.h"
#include "dto_handler/player_dto_parser.h"

namespace DTO {
class GameStateDTO;
};

namespace Model {
class Player;
};

namespace View {
class SDLRenderer;
};

namespace Controller {
class GameStateManager {
friend class View::SDLRenderer;

private:
    std::mutex mutex;
    short_id_t reference_player_id;
    Shared<Model::GameState> game_state;
    DTO::PlayerDTOParser player_dto_parser;

protected:
    // Unsafe functions, only used by friend classes
    short_id_t get_reference_player_id();
    Model::Player& get_reference_player();

public:
    GameStateManager(short_id_t reference_player_id);

    void map_function_on_players(std::function<void(const Model::Player&)> function);
    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};

#endif // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
