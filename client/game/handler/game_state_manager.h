#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <functional>
#include <mutex>

#include "common/definitions.h"

#include "dto_handler/player_dto_parser.h"
#include "render/camera.h"

namespace SDL2pp {
class Window;
};

namespace DTO {
class GameStateDTO;
};

namespace Model {
class GameState;
class Player;
};

namespace Controller {
class GameStateManager {

private:
    std::mutex mutex;
    Shared<Model::GameState> game_state;
    DTO::PlayerDTOParser player_dto_parser;
    short_id_t reference_player_id;
    Weak<SDL2pp::Window> window;
    View::Camera camera;

public:
    GameStateManager(
        short_id_t reference_player_id,
        Weak<SDL2pp::Window> window
    );

    View::Camera get_camera();

    void map_function_on_players(const std::function<void(Model::Player&)>& func);

    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};

#endif // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
