#ifndef CLIENT_GAME_SOUND_DISTANCED_SOUND_H
#define CLIENT_GAME_SOUND_DISTANCED_SOUND_H

#include "asset/sound_id.h"
#include "common/definitions.h"
#include "interface/fixed.h"

#include "sound_effect.h"

namespace Controller {
class GameController;
};

namespace View {
class DistancedSoundEffect: public SoundEffect, public Fixed {
private:
    SDL2pp::Point position;

    int calculate_volume(int current_distance, int min_range, int max_range);
    void update_volume();

public:
    DistancedSoundEffect(Weak<Controller::BaseController> controller, Model::SoundID sound_id);

    void set_position(const SDL2pp::Point& new_poisition);
    virtual void play() override;

    virtual ~DistancedSoundEffect() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_SOUND_DISTANCED_SOUND_H
