#ifndef CLIENT_GAME_ANIMATION_ANIMATION_H
#define CLIENT_GAME_ANIMATION_ANIMATION_H

#include "interface/rendered.h"

namespace Controller {
class BaseController;
};

namespace View {
class Animation: public Rendered {
protected:
    bool ended;

public:
    explicit Animation(Weak<Controller::BaseController> controller);

    virtual bool has_ended() const;
    void end();

    virtual ~Animation() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ANIMATION_ANIMATION_H
