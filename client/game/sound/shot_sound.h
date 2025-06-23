#ifndef CLIENT_GAME_SOUND_SHOT_SOUND_H
#define CLIENT_GAME_SOUND_SHOT_SOUND_H

#include "sound_effect.h"

namespace Controller {
class GameController;
};

namespace View {
class ShotSound: public SoundEffect {
public:
    ShotSound(
        Weak<Controller::GameController> controller,
        short_id_t player_id,
        Model::WeaponID weapon_id
    );

    ~ShotSound() override = default;
};
};

#endif // CLIENT_GAME_SOUND_SHOT_SOUND_H
