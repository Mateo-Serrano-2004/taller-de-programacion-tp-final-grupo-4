#ifndef CLIENT_GAME_ANIMATION_INTERPOLATED_ANIMATION_H
#define CLIENT_GAME_ANIMATION_INTERPOLATED_ANIMATION_H

#include "controller/base_controller.h"

#include "animation.h"

namespace View {
class InterpolatedAnimation: public Animation {
protected:
    // In a range [0, 100]
    int current_progression;

public:
    explicit InterpolatedAnimation(Weak<Controller::BaseController> controller);

    virtual void progress(int value);

    ~InterpolatedAnimation() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ANIMATION_INTERPOLATED_ANIMATION_H
