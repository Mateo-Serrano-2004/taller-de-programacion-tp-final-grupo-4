#ifndef CLIENT_GAME_RENDER_MAP_RENDERER_H
#define CLIENT_GAME_RENDER_MAP_RENDERER_H

#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

namespace SDL2pp {
class Texture;
class Renderer;
};  // namespace SDL2pp

namespace Controller {
class GameController;
};

namespace Model {
class GameState;
};

namespace View {
class Camera;

class MapRenderer {
private:
    Shared<SDL2pp::Renderer> renderer;
    SDL2pp::Rect get_map_slice(Shared<SDL2pp::Texture> map, const Camera& camera);
    SDL2pp::Rect get_viewport_slice(const SDL2pp::Rect& map_slice, const Camera& camera);

public:
    explicit MapRenderer(Weak<Controller::GameController> controller);

    void render_map(const Model::GameState& game_state);

    ~MapRenderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_MAP_RENDERER_H
