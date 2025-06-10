#ifndef CLIENT_GAME_RENDER_PLAYER_RENDERER_H
#define CLIENT_GAME_RENDER_PLAYER_RENDERER_H

#include <map>

#include <SDL2pp/Point.hh>

#include "common/definitions.h"

#include "asset/texture_id.h"

#include "entity/pane.h"

#include "renderer.h"

namespace SDL2pp {
class Font;
};

namespace Model {
class Player;
};

namespace Controller {
class GameController;
class GameStateManager;
};

namespace View {
class Camera;
class RenderedPlayer;

class PlayerRenderer: public Renderer {
protected:
    Pane background;
    Shared<Controller::GameStateManager> game_state_manager;
    Shared<SDL2pp::Font> font;

    SDL2pp::Point get_sprite_top_left_corner(short_id_t sprite_piece);

    void render_weapon(const SDL2pp::Point& player_center, angle_t player_angle, Model::TextureID texture_id);
    void render_name(const SDL2pp::Point& player_center, const std::string& player);
    void render_player(Camera& camera, Shared<View::RenderedPlayer>& player);
    void render_fov(angle_t angle);

public:
    PlayerRenderer(Weak<Controller::GameController> controller);

    void render() override;
    void update_size();

    ~PlayerRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_PLAYER_RENDERER_H
