#ifndef CLIENT_GAME_ANIMATION_ANIMATION_H
#define CLIENT_GAME_ANIMATION_ANIMATION_H

#include <cstdint>

#include "common/definitions.h"
#include "interface/rendered.h"

namespace Controller {
class BaseController;
};

namespace View {
class Animation: public Rendered {
protected:
    int current_frame;
    bool ended;
    int total_frames;

public:
    explicit Animation(
        Weak<Controller::BaseController> controller,
        int total_frames = 0
    );

    virtual void step(int frames);
    virtual bool has_ended() const;
    void end();

    virtual ~Animation() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ANIMATION_ANIMATION_H
