#include "framed_animation.h"

#include <SDL2pp/Renderer.hh>

#include "controller/base_controller.h"

View::FramedAnimation::FramedAnimation(Weak<Controller::BaseController> controller):
        View::Animation(controller), current_frame(0), total_frames(0) {}

void View::FramedAnimation::step(int frames) {
    if (has_ended())
        return;
    render();
    current_frame += frames;
    ended = (current_frame >= total_frames);
}
