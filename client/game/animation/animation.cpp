#include "animation.h"

#include "controller/base_controller.h"

View::Animation::Animation(Weak<Controller::BaseController> controller):
        View::Rendered(controller), ended(false) {}

bool View::Animation::has_ended() const { return ended; }

void View::Animation::end() { ended = true; }
