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

    void load_animation(Shared<Model::GameState>& new_game_state, const Shared<View::RenderedPlayer>& player);
    void load_shot_sound(Shared<Model::GameState>& new_game_state, const Shared<View::RenderedPlayer>& player);
    void load_reload_sound(Shared<Model::GameState>& new_game_state, const Shared<View::RenderedPlayer>& player);
    void load_bomb_explosion(DTO::GameStateDTO& dto);
    void load_start_round_sound(DTO::GameStateDTO& dto, const Shared<View::RenderedPlayer>& player);
    void load_bomb_state_sound(DTO::GameStateDTO& dto);
    void winner_sound(DTO::GameStateDTO& dto);

    void update_dropped_weapons(DTO::GameStateDTO& dto);
    void update_animations(Shared<Model::GameState>& new_game_state);
    void update_sounds(Shared<Model::GameState>& new_game_state);
    void update_camera(const Shared<View::RenderedPlayer>& ref_player);
    void update_bomb_position(DTO::GameStateDTO& dto);
    void update_progress_bar(const Shared<View::RenderedPlayer>& ref_player);
    void update_winner_message(DTO::GameStateDTO& dto);
    void update_stats(DTO::GameStateDTO& dto);

public:
    explicit GameStateManager(Weak<GameController> controller);

    Model::GameState get_game_state();

    void update_player_id(short_id_t new_id);
    void update_map(Shared<SDL2pp::Texture> new_map);
    void update(DTO::GameStateDTO& game_state_dto);

    ~GameStateManager() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
