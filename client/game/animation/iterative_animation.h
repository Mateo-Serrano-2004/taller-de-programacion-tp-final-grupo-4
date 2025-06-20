#ifndef CLIENT_GAME_ANIMATION_ITERATIVE_ANIMATION_H
#define CLIENT_GAME_ANIMATION_ITERATIVE_ANIMATION_H

#include <cstdint>

#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>

#include "asset/animation_id.h"
#include "common/definitions.h"
#include "render/camera.h"

#include "animation.h"
#include "animation_details.h"

namespace Controller {
class BaseController;
class AnimationIterator;
};

namespace View {
class RenderedPlayer;

class IterativeAnimation: public Animation {
protected:
    Model::AnimationDetails details;

    virtual SDL2pp::Rect get_frame();

    virtual SDL2pp::Rect get_dsrect() = 0;
    virtual angle_t get_angle() = 0;
    virtual SDL2pp::Point get_rpoint() = 0;

public:
    IterativeAnimation(Weak<Controller::BaseController> controller, Model::AnimationID id);

    void render() override;

    ~IterativeAnimation() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ANIMATION_ITERATIVE_ANIMATION_H
