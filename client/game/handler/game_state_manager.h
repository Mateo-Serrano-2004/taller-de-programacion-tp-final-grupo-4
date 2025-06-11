#ifndef CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
#define CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H

#include <functional>
#include <list>
#include <mutex>
#include <map>

#include "common/definitions.h"

#include "asset/texture_id.h"

#include "enum/enum_translator.h"

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

namespace View {
class RenderedPlayer;
};

namespace Controller {
class GameStateManager {

private:
    std::mutex mutex;
    std::list<Shared<View::RenderedPlayer>> pending_weapon_usages;
    Model::EnumTranslator enum_translator;
    Shared<Model::GameState> game_state;
    short_id_t reference_player_id;
    Weak<SDL2pp::Window> window;
    View::Camera camera;

    void add_player_shooting(Shared<View::RenderedPlayer> player);

public:
    GameStateManager(
        short_id_t reference_player_id,
        Weak<SDL2pp::Window> window
    );

    View::Camera get_camera();

    short_id_t get_reference_player_id() const;
    Shared<View::RenderedPlayer> get_reference_player();

    void update_player_sprite(Model::TextureID texture_id);

    void map_function_on_players(
        const std::function<void(Shared<View::RenderedPlayer>&)>& func
    );
    void call_function_on_players(
        const std::function<void(std::map<short_id_t, Shared<View::RenderedPlayer>>&)>& func
    );
    void map_function_on_pending_weapon_usages(
        const std::function<void(Shared<View::RenderedPlayer>&)>& func
    );

    void update_camera();

    uint16_t get_time_left();

    void update(DTO::GameStateDTO&& game_state_dto);

    ~GameStateManager() = default;
};
};

#endif // CLIENT_GAME_HANDLER_GAME_STATE_MANAGER_H
