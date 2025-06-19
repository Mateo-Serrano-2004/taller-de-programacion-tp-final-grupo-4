#include "animation_iterator.h"

#include <SDL2pp/Rect.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

SDL2pp::Rect Controller::AnimationIterator::get_frame() {
    if (current_frame == details.total_frames)
        ended = true;
    return SDL2pp::Rect(
            ((current_frame / details.animation_duration_in_frames) % details.width) * 32,
            ((current_frame / details.animation_duration_in_frames) / details.width) * 32, 32, 32);
}

void Controller::AnimationIterator::step(uint8_t frames) {
    current_frame += frames;
    if (current_frame > details.total_frames)
        ended = true;
}

Controller::AnimationIterator::AnimationIterator(const Model::AnimationDetails& details):
        current_frame(0), ended(false), details(details) {}

bool Controller::AnimationIterator::has_ended() const { return ended; }
