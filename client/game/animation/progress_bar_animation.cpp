#include "progress_bar_animation.h"

#include "controller/base_controller.h"

View::ProgressBarAnimation::ProgressBarAnimation(Weak<Controller::BaseController> controller)
: View::InterpolatedAnimation(controller),
  viewport(controller),
  progress_bar(controller) {
    viewport.add_child(&progress_bar);
    viewport.set_vertical_alignment(0.1);

    progress_bar.set_background_color(255, 255, 255, 255);
    progress_bar.set_draw_background(true);
    progress_bar.set_height(15);
    progress_bar.set_width(1);
}

void View::ProgressBarAnimation::render() {
    if (current_progression)
        progress_bar.set_width(current_progression);
    viewport.render();
}
