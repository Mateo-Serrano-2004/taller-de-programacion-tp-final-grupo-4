#ifndef CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H
#define CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H

#include <cstdint>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

#include "iterative_animation.h"

namespace Controller {
class GameController;
class AnimationIterator;
};  // namespace Controller

namespace View {
class RenderedPlayer;

class MuzzleFireAnimation: public IterativeAnimation {
protected:
    Shared<RenderedPlayer> player;
    short_id_t player_id;

    int get_fire_distance();

    int get_frame_size() override;
    SDL2pp::Rect get_dsrect() override;
    angle_t get_angle() override;
    SDL2pp::Point get_rpoint() override;

public:
    MuzzleFireAnimation(Weak<Controller::GameController> controller, short_id_t player_id);

    short_id_t get_player_id() const;

    void set_player(Shared<RenderedPlayer> new_player);

    bool has_ended() const override;

    ~MuzzleFireAnimation() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H
