#include "iterative_animation.h"

#include <algorithm>

#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

View::IterativeAnimation::IterativeAnimation(Weak<Controller::BaseController> controller,
                                             Model::AnimationID id):
        View::FramedAnimation(controller),
        details(controller.lock()->get_asset_manager()->get_animation(id)) {
    total_frames = details.animation_duration_in_frames;
}

SDL2pp::Rect View::IterativeAnimation::get_frame() {
    float progress = static_cast<float>(current_frame) / total_frames;
    int frame_index = static_cast<int>(progress * details.total_frames);
    frame_index = std::min(frame_index, static_cast<int>(details.total_frames - 1));

    int col = frame_index % details.width;
    int row = frame_index / details.width;

    int frame_size = get_frame_size();

    return SDL2pp::Rect(col * frame_size, row * frame_size, frame_size, frame_size);
}


void View::IterativeAnimation::render() {
    renderer->Copy(*details.animation, get_frame(), get_dsrect(), get_angle(), get_rpoint());
}
