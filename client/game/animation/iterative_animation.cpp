#include "iterative_animation.h"

#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

View::IterativeAnimation::IterativeAnimation(Weak<Controller::BaseController> controller,
                                             Model::AnimationID id):
        View::FramedAnimation(controller),
        details(controller.lock()->get_asset_manager()->get_animation(id)) {
    total_frames = details.total_frames;
}

SDL2pp::Rect View::IterativeAnimation::get_frame() {
    return SDL2pp::Rect(
            ((current_frame / details.animation_duration_in_frames) % details.width) * 32,
            ((current_frame / details.animation_duration_in_frames) / details.width) * 32, 32, 32);
}

void View::IterativeAnimation::render() {
    renderer->Copy(*details.animation, get_frame(), get_dsrect(), get_angle(), get_rpoint());
}
