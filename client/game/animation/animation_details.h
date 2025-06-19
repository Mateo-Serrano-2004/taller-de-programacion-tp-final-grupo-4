#ifndef CLIENT_GAME_ANIMATION_ANIMATION_DETAILS_H
#define CLIENT_GAME_ANIMATION_ANIMATION_DETAILS_H

#include <cstdint>

#include "common/definitions.h"

namespace SDL2pp {
class Texture;
}

namespace Model {
struct AnimationDetails {
public:
    uint8_t width;
    uint8_t height;
    uint8_t total_frames;
    uint8_t animation_duration_in_frames;
    Shared<SDL2pp::Texture> animation;

    AnimationDetails(uint8_t width, uint8_t height, uint8_t total_frames,
                     uint8_t animation_duration_in_frames, Shared<SDL2pp::Texture> animation);

    ~AnimationDetails() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_ANIMATION_ANIMATION_DETAILS_H
