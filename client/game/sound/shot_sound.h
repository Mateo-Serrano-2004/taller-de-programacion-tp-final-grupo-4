#ifndef CLIENT_GAME_SOUND_SHOT_SOUND_H
#define CLIENT_GAME_SOUND_SHOT_SOUND_H

#include "tracking_sound_effect.h"

namespace Controller {
class GameController;
};

namespace View {
class ShotSound: public TrackingSoundEffect {
public:
    ShotSound(Weak<Controller::GameController> controller, Model::WeaponID weapon_id,
              short_id_t player_id);

    ~ShotSound() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_SOUND_SHOT_SOUND_H
