#ifndef COMMON_MODEL_GAME_STATE_H
#define COMMON_MODEL_GAME_STATE_H

#include <cstdint>
#include <list>
#include <map>
#include <vector>

#include "common/definitions.h"
#include "common/round_state.h"
#include "common/team.h"
#include "render/camera.h"

namespace SDL2pp {
class Texture;
class Point;
}  // namespace SDL2pp

namespace Controller {
class GameStateManager;
};

namespace View {
class RenderedPlayer;
class MuzzleFireAnimation;
class WinnerTeamMessageAnimation;
class ProgressBarAnimation;
class BombExplosionAnimation;
class TrackingSoundEffect;
class SoundEffect;
class DistancedSoundEffect;
};  // namespace View

namespace DTO {
struct DropWeaponDTO;
};

namespace Model {
struct GameState {
public:
    std::map<short_id_t, Shared<View::RenderedPlayer>> players;
    std::vector<Shared<DTO::DropWeaponDTO>> dropped_weapons;
    std::list<Shared<View::MuzzleFireAnimation>> fires;
    std::list<Shared<View::TrackingSoundEffect>> sound_effects;
    std::list<Shared<View::TrackingSoundEffect>> death_sound_effect;
    std::list<Shared<View::TrackingSoundEffect>> hit_sound_effect;
    Shared<View::SoundEffect> start_round_radio;
    Shared<View::SoundEffect> bomb_state_sound;
    Shared<View::WinnerTeamMessageAnimation> winner_message;
    Shared<View::ProgressBarAnimation> progress_bar;
    Shared<View::BombExplosionAnimation> bomb_explosion;
    Shared<View::DistancedSoundEffect> bomb_explosion_sound;
    Shared<View::SoundEffect> winner_sound;
    View::Camera camera;
    Shared<SDL2pp::Texture> map;
    Maybe<short_id_t> reference_player_id;
    bool bomb_defused;
    bool bomb_planted;
    Maybe<SDL2pp::Point> bomb_position;
    uint16_t time_left;
    uint8_t defusing_progress;
    uint8_t first_team_victories;
    uint8_t second_team_victories;
    Model::TeamID round_winner;
    Model::TeamID game_winner;
    RoundState round_state;

    GameState();
    GameState(const GameState&) = default;
    GameState& operator=(const GameState&) = default;

    Shared<View::RenderedPlayer> get_reference_player() const;
    Shared<View::RenderedPlayer> get_player_by_id(Maybe<short_id_t> id) const;
    Shared<View::RenderedPlayer> get_any_player_by_team(Model::TeamID team) const;
    Shared<View::RenderedPlayer> get_any_player_alive() const;
    Shared<View::RenderedPlayer> get_any_player_alive_by_team(Model::TeamID team) const;

    ~GameState() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_GAME_STATE_H
