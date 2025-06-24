#ifndef CLIENT_GAME_ANIMATION_BOMB_EXPLOSION_ANIMATION_H
#define CLIENT_GAME_ANIMATION_BOMB_EXPLOSION_ANIMATION_H

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"
#include "interface/fixed.h"

#include "iterative_animation.h"

namespace Controller {
class GameController;
};

namespace View {
class BombExplosionAnimation: public IterativeAnimation, public Fixed {
private:
    SDL2pp::Point bomb_position;

    int get_frame_size() override;
    SDL2pp::Rect get_dsrect() override;
    angle_t get_angle() override;
    SDL2pp::Point get_rpoint() override;

public:
    BombExplosionAnimation(Weak<Controller::GameController> controller,
                           const SDL2pp::Point& bomb_position);

    ~BombExplosionAnimation() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ANIMATION_BOMB_EXPLOSION_ANIMATION_H
