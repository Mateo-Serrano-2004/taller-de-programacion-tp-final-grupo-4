#ifndef CLIENT_GAME_RENDER_PLAYER_RENDERER_H
#define CLIENT_GAME_RENDER_PLAYER_RENDERER_H

#include <SDL2pp/Point.hh>

#include "common/definitions.h"

namespace SDL2pp {
class Window;
class Renderer;
};

namespace Model {
class Player;
class TextureStorage;
};

namespace Controller {
class GameController;
class GameStateManager;
};

namespace View {
class Camera;

class PlayerRenderer {
protected:
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::TextureStorage> texture_storage;
    Shared<Controller::GameStateManager> game_state_manager;

    SDL2pp::Point get_skin_top_left_corner(short_id_t skin_piece);
    void render_player(Camera& camera, Model::Player& player);
    void render_fov();

public:
    PlayerRenderer(Weak<Controller::GameController> controller);

    void render();

    ~PlayerRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_PLAYER_RENDERER_H
