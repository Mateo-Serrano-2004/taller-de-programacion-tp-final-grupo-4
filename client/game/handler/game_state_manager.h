#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <functional>
#include <list>
#include <map>
#include <mutex>

#include "animation/muzzle_fire_animation.h"
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
    std::list<View::MuzzleFireAnimation> fire_animations;
    Shared<SDL2pp::Texture> map;
    Maybe<short_id_t> reference_player_id;
    Shared<Model::GameState> game_state;
    View::Camera camera;
    Weak<GameController> controller;

public:
    explicit GameStateManager(Weak<GameController> controller);

    Shared<View::RenderedPlayer> get_reference_player_unsafe();
    Shared<View::RenderedPlayer> get_player_by_id_unsafe(short_id_t player_id);
    View::Camera get_camera_unsafe();

    Shared<View::RenderedPlayer> get_reference_player();

    void call_function_on_players(
            const std::function<void(std::map<short_id_t, Shared<View::RenderedPlayer>>&)>& func);
    void call_function_on_pending_fires(
            const std::function<void(std::list<View::MuzzleFireAnimation>&)>& func);

    uint16_t get_time_left();
    View::Camera get_camera();
    Shared<SDL2pp::Texture> get_map();

    void update_player_id(short_id_t new_id);
    void update_map(Shared<SDL2pp::Texture> new_map);
    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
