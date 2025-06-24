#ifndef CLIENT_GAME_RENDER_PLAYER_RENDERER_H
#define CLIENT_GAME_RENDER_PLAYER_RENDERER_H

#include <cstdint>
#include <map>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "asset/texture_id.h"
#include "common/definitions.h"
#include "entity/pane.h"
#include "sound/sound_effect_player.h"

#include "animation_renderer.h"
#include "dropped_weapon_renderer.h"
#include "map_renderer.h"
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
    AnimationRenderer animation_renderer;
    SoundEffectPlayer sound_player;
    MapRenderer map_renderer;
    DroppedWeaponRenderer weapon_renderer;
    Shared<Controller::GameStateManager> game_state_manager;
    Shared<SDL2pp::Texture> bomb_texture;

    void render_fov(const Model::GameState& game_state);
    void render_bomb(const Model::GameState& game_state);
    bool render_players(const Model::GameState& game_state);

public:
    explicit PlayerRenderer(Weak<Controller::GameController> controller);

    void render(const Model::GameState& game_state, uint8_t frames) override;

    ~PlayerRenderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_PLAYER_RENDERER_H
