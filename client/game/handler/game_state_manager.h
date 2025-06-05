#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <functional>
#include <mutex>
#include <map>

#include "common/definitions.h"
#include "common/texture_id.h"

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

    short_id_t get_reference_player_id() const;

    void update_player_sprite(Model::TextureID texture_id);

    void map_function_on_players(const std::function<void(Model::Player&)>& func);
    void call_function_on_players(const std::function<void(std::map<short_id_t, Model::Player>&)>& func);

    void update_camera();

    uint16_t get_time_left();

    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};

#endif // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
