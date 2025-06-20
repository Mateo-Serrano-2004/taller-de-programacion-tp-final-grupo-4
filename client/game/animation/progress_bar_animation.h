#ifndef CLIENT_GAME_ANIMATION_PROGRESS_BAR_ANIMATION_H
#define CLIENT_GAME_ANIMATION_PROGRESS_BAR_ANIMATION_H

#include "entity/vertical_pane.h"
#include "entity/horizontal_pane.h"

#include "interpolated_animation.h"

namespace Controller {
class BaseController;
};

namespace View {
class ProgressBarAnimation: public InterpolatedAnimation {
private:
    HorizontalPane viewport;
    HorizontalPane progress_bar;

public:
    ProgressBarAnimation(Weak<Controller::BaseController> controller);

    void render() override;

    ~ProgressBarAnimation() override = default;
};
};

#endif // CLIENT_GAME_ANIMATION_PROGRESS_BAR_ANIMATION_H
