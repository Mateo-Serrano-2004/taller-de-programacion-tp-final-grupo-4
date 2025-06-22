#ifndef CLIENT_GAME_ANIMATION_FRAMED_ANIMATION_H
#define CLIENT_GAME_ANIMATION_FRAMED_ANIMATION_H

#include <cstdint>

#include "common/definitions.h"

#include "animation.h"

namespace Controller {
class BaseController;
};

namespace View {
class FramedAnimation: public Animation {
protected:
    int current_frame;
    int total_frames;

public:
    explicit FramedAnimation(Weak<Controller::BaseController> controller);

    virtual void step(int frames);

    virtual ~FramedAnimation() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ANIMATION_FRAMED_ANIMATION_H
