#include "animation_details.h"

#include <cstdint>

#include <SDL2pp/Texture.hh>

Model::AnimationDetails::AnimationDetails(uint8_t width, uint8_t height, uint8_t total_frames,
                                          uint8_t animation_duration_in_frames,
                                          Shared<SDL2pp::Texture> animation):
        width(width),
        height(height),
        total_frames(total_frames),
        animation_duration_in_frames(animation_duration_in_frames),
        animation(animation) {}
