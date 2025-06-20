#ifndef COMMON_MODEL_GAME_STATE_H
#define COMMON_MODEL_GAME_STATE_H

#include <cstdint>
#include <list>
#include <map>

#include "common/definitions.h"
#include "common/team.h"
#include "render/camera.h"

namespace SDL2pp {
class Texture;
class Point;
}

namespace Controller {
class GameStateManager;
};

namespace View {
class RenderedPlayer;
class MuzzleFireAnimation;
class WinnerTeamMessageAnimation;
};  // namespace View

namespace Model {
struct GameState {
public:
    std::map<short_id_t, Shared<View::RenderedPlayer>> players;
    std::list<Shared<View::MuzzleFireAnimation>> fires;
    Shared<View::WinnerTeamMessageAnimation> winner_message;
    View::Camera camera;
    Shared<SDL2pp::Texture> map;
    Maybe<short_id_t> reference_player_id;
    Maybe<SDL2pp::Point> bomb_position;
    uint16_t time_left;
    uint8_t first_team_victories;
    uint8_t second_team_victories;
    Model::TeamID round_winner;
    Model::TeamID game_winner;

    GameState();
    GameState(const GameState& other);

    Shared<View::RenderedPlayer> get_reference_player() const;
    Shared<View::RenderedPlayer> get_player_by_id(Maybe<short_id_t> id) const;

    ~GameState() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_GAME_STATE_H
