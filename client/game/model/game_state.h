#ifndef COMMON_MODEL_GAME_STATE_H
#define COMMON_MODEL_GAME_STATE_H

#include <cstdint>
#include <list>
#include <map>

#include "animation/muzzle_fire_animation.h"
#include "common/definitions.h"
#include "render/camera.h"

namespace SDL2pp {
class Texture;
}

namespace Controller {
class GameStateManager;
};

namespace View {
class RenderedPlayer;
class MuzzleFireAnimation;
};  // namespace View

namespace Model {
struct GameState {
public:
    std::map<short_id_t, Shared<View::RenderedPlayer>> players;
    std::list<Shared<View::MuzzleFireAnimation>> fires;
    View::Camera camera;
    Shared<SDL2pp::Texture> map;
    Maybe<short_id_t> reference_player_id;
    uint16_t time_left;

    GameState();
    GameState(const GameState& other);

    Shared<View::RenderedPlayer> get_reference_player() const;
    Shared<View::RenderedPlayer> get_player_by_id(Maybe<short_id_t> id) const;

    ~GameState() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_GAME_STATE_H
