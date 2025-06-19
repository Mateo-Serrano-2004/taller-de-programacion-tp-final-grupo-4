#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <mutex>
#include <list>
#include <map>

#include "asset/texture_id.h"
#include "common/definitions.h"
#include "render/camera.h"
#include "utils/enum_translator.h"

#include "render/render_context.h"
#include "render/full_render_context.h"

namespace SDL2pp {
class Texture;
};

namespace DTO {
class GameStateDTO;
};

namespace Model {
class GameState;
class Player;
};  // namespace Model

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
    Weak<GameController> controller;

public:
    explicit GameStateManager(Weak<GameController> controller);

    Model::RenderContext get_render_context();
    Model::FullRenderContext get_full_render_context();

    void update_player_id(short_id_t new_id);
    void update_map(Shared<SDL2pp::Texture> new_map);
    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};

#endif  // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
