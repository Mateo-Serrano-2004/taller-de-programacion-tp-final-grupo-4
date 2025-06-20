#ifndef CLIENT_GAME_MODEL_RENDERED_PLAYER_H
#define CLIENT_GAME_MODEL_RENDERED_PLAYER_H

#include <cstdint>
#include <string>

#include <SDL2pp/Point.hh>

#include "asset/texture_id.h"
#include "common/definitions.h"
#include "common/model/player.h"
#include "common/model/vector_2d.h"
#include "common/model/weapon.h"
#include "common/role_id.h"
#include "common/weapon_id.h"
#include "interface/fixed.h"
#include "interface/rendered.h"
#include "render/camera.h"

namespace SDL2pp {
class Renderer;
class Point;
};  // namespace SDL2pp

namespace Model {
class AssetManager;
};

namespace Controller {
class GameController;
};

namespace View {
class RenderedPlayer: public Rendered, public Fixed, public Model::Player {
protected:
    Shared<Model::AssetManager> asset_manager;

    Model::TextureID sprite_id;
    short_id_t sprite_piece;
    Model::TextureID weapon_sprite_id;

    short_id_t get_sprite_piece_from_weapon();

    SDL2pp::Point get_sprite_top_left_corner();
    void render_weapon(const SDL2pp::Point& player_center);
    void render_name(const SDL2pp::Point& player_center);

public:
    RenderedPlayer(Weak<Controller::GameController> controller, Model::Player&& player);

    void render() override;

    ~RenderedPlayer() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_MODEL_RENDERED_PLAYER_H
