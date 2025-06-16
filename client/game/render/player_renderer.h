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

    void render_fov(angle_t angle, const Camera& camera);

public:
    PlayerRenderer(Weak<Controller::GameController> controller);

    void render() override;

    ~PlayerRenderer() = default;
};
};

#endif // CLIENT_GAME_RENDER_PLAYER_RENDERER_H
