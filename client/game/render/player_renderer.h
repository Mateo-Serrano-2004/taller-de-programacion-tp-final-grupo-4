#ifndef CLIENT_GAME_RENDER_PLAYER_RENDERER_H
#define CLIENT_GAME_RENDER_PLAYER_RENDERER_H

#include <cstdint>
#include <map>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "asset/texture_id.h"
#include "common/definitions.h"
#include "entity/pane.h"

#include "renderer.h"

namespace SDL2pp {
class Font;
};

namespace Controller {
class GameController;
class GameStateManager;
};  // namespace Controller

namespace View {
class Camera;
class RenderedPlayer;

class PlayerRenderer: public Renderer {
protected:
    Shared<Controller::GameStateManager> game_state_manager;
    Shared<SDL2pp::Font> font;

    void render_winner_message(const Model::GameState& game_state, uint8_t frames);
    void render_fov(const Model::GameState& game_state);
    void render_muzzle_fires(const Model::GameState& game_state, uint8_t frames);
    bool render_players(const Model::GameState& game_state);

    SDL2pp::Rect get_map_slice(Shared<SDL2pp::Texture> map, const Camera& camera);
    SDL2pp::Rect get_viewport_slice(const SDL2pp::Rect& map_slice, const Camera& camera);
    void render_map(const Model::GameState& game_state);

public:
    explicit PlayerRenderer(Weak<Controller::GameController> controller);

    void render(const Model::GameState& game_state, uint8_t frames) override;

    ~PlayerRenderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_PLAYER_RENDERER_H
