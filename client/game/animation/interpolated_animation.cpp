#include "interpolated_animation.h"

View::InterpolatedAnimation::InterpolatedAnimation(Weak<Controller::BaseController> controller):
        View::Animation(controller) {
    current_progression = 0;
}

void View::InterpolatedAnimation::progress(int value) {
    if (ended)
        return;
    render();
    current_progression = value;
    ended = current_progression > 100;
}
