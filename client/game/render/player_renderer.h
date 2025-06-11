#ifndef CLIENT_GAME_RENDER_PLAYER_RENDERER_H
#define CLIENT_GAME_RENDER_PLAYER_RENDERER_H

#include <map>
#include <list>

#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>

#include <SDL2pp/Point.hh>

#include "common/definitions.h"

#include "asset/texture_id.h"

#include "entity/pane.h"

#include "functor/scalator.h"

#include "enum/enum_translator.h"

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
    Model::EnumTranslator translator;
    std::list<Pane> game_sprites;
    SDL2pp::Mixer mixer;
    SDL2pp::Chunk chunk;
    Weak<Controller::GameController> controller;
    Scalator scalator;
    Pane background;
    Shared<Controller::GameStateManager> game_state_manager;
    Shared<SDL2pp::Font> font;

    void set_player_to_be_rendered(
        Shared<View::RenderedPlayer> player,
        const SDL2pp::Point& camera_view,
        const SDL2pp::Point& player_display_size
    );
    void set_weapon_to_be_rendered(
        Shared<View::RenderedPlayer> player,
        const SDL2pp::Point& camera_view,
        const SDL2pp::Point& player_display_size
    );
    void set_name_to_be_rendered(
        Shared<View::RenderedPlayer> player,
        const SDL2pp::Point& camera_view,
        const SDL2pp::Point& player_display_size
    );

    SDL2pp::Point get_sprite_top_left_corner(short_id_t sprite_piece);

    void load_player(Camera& camera, Shared<View::RenderedPlayer>& player);
    void load_fov(angle_t angle);

public:
    PlayerRenderer(Weak<Controller::GameController> controller);

    void render() override;
    void update_size();

    ~PlayerRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_PLAYER_RENDERER_H
