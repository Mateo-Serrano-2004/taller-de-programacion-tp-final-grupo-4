#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <functional>
#include <list>
#include <mutex>
#include <map>

#include "common/definitions.h"

#include "asset/texture_id.h"

#include "utils/enum_translator.h"

#include "render/camera.h"

namespace DTO {
class GameStateDTO;
};

namespace Model {
class GameState;
class Player;
};

namespace View {
class RenderedPlayer;
};

namespace Controller {
class GameController;

class GameStateManager {

private:
    std::mutex mutex;
    Maybe<short_id_t> reference_player_id;
    Shared<Model::GameState> game_state;
    View::Camera camera;
    Weak<GameController> controller;

public:
    GameStateManager(Weak<GameController> controller);

    Shared<View::RenderedPlayer> get_reference_player_unsafe();
    Shared<View::RenderedPlayer> get_reference_player();

    void call_function_on_players(
        const std::function<void(std::map<short_id_t, Shared<View::RenderedPlayer>>&)>& func
    );

    uint16_t get_time_left();
    View::Camera get_camera();

    void update_player_id(short_id_t new_id);
    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};

#endif // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
