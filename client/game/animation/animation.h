#ifndef CLIENT_GAME_ANIMATION_ANIMATION_H
#define CLIENT_GAME_ANIMATION_ANIMATION_H

#include <cstdint>

#include "common/definitions.h"

#include "asset/animation_id.h"

#include "interface/rendered.h"

#include "animation_iterator.h"

namespace Controller {
class GameController;
class GameStateManager;
};

namespace View {
class Animation: public Rendered, public Controller::AnimationIterator {
protected:
    uint8_t frames_to_process;
    Shared<Controller::GameStateManager> game_state_manager;

public:
    Animation(
        Weak<Controller::GameController> controller,
        Model::AnimationID id
    );

    void set_frames_to_process(uint8_t frames);

    virtual ~Animation() = default;
};
};

#endif // CLIENT_GAME_ANIMATION_ANIMATION_H
