#ifndef CLIENT_GAME_ANIMATION_ANIMATION_ITERATOR_H
#define CLIENT_GAME_ANIMATION_ANIMATION_ITERATOR_H

#include <SDL2pp/Rect.hh>

#include "asset/animation_id.h"
#include "common/definitions.h"

#include "animation_details.h"

namespace SLD2pp {
class Texture;
};

namespace Controller {
class BaseController;

class AnimationIterator {
protected:
    uint8_t current_frame;
    bool ended;
    Model::AnimationDetails details;

    virtual SDL2pp::Rect get_frame();

    virtual void step(uint8_t frames);

public:
    explicit AnimationIterator(const Model::AnimationDetails& details);

    bool has_ended() const;

    virtual ~AnimationIterator() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_ANIMATION_ANIMATION_ITERATOR_H
