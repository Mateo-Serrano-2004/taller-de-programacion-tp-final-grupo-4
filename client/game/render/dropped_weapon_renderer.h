#ifndef CLIENT_GAME_RENDER_DROPPED_WEAPON_RENDERER_H
#define CLIENT_GAME_RENDER_DROPPED_WEAPON_RENDERER_H

#include "common/definitions.h"

namespace SDL2pp {
class Renderer;
};

namespace Controller {
class GameController;
};

namespace Model {
struct GameState;
class AssetManager;
};  // namespace Model

namespace View {
class DroppedWeaponRenderer {
private:
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::AssetManager> manager;

public:
    explicit DroppedWeaponRenderer(Weak<Controller::GameController> controller);

    void render_weapons(const Model::GameState& game_state);

    ~DroppedWeaponRenderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_DROPPED_WEAPON_RENDERER_H
