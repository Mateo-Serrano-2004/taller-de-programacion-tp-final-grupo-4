#ifndef CLIENT_GAME_RENDER_PLAYER_RENDERER_H
#define CLIENT_GAME_RENDER_PLAYER_RENDERER_H

#include <SDL2pp/Point.hh>

#include "common/definitions.h"

#include "renderer.h"

namespace Model {
class Player;
};

namespace Controller {
class GameController;
class GameStateManager;
};

namespace View {
class Camera;

class PlayerRenderer: public Renderer {
protected:
    Shared<Controller::GameStateManager> game_state_manager;

    SDL2pp::Point get_skin_top_left_corner(short_id_t skin_piece);
    void render_player(Camera& camera, Model::Player& player);
    void render_fov();

public:
    PlayerRenderer(Weak<Controller::GameController> controller);

    void render() override;

    ~PlayerRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_PLAYER_RENDERER_H
