#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <list>
#include <map>
#include <mutex>

#include "asset/texture_id.h"
#include "common/definitions.h"
#include "render/camera.h"
#include "utils/enum_translator.h"

namespace SDL2pp {
class Texture;
};

namespace DTO {
class GameStateDTO;
};

namespace Model {
struct GameState;
};

namespace View {
class RenderedPlayer;
};

namespace Controller {
class GameController;

class GameStateManager {
private:
    std::mutex mutex;
    Shared<Model::GameState> game_state;
    Weak<GameController> controller;

public:
    explicit GameStateManager(Weak<GameController> controller);

    Model::GameState get_game_state();

    void update_player_id(short_id_t new_id);
    void update_map(Shared<SDL2pp::Texture> new_map);
    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
