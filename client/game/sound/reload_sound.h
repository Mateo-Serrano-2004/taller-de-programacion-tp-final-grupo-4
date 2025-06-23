#ifndef CLIENT_GAME_SOUND_RELOAD_SOUND_H
#define CLIENT_GAME_SOUND_RELOAD_SOUND_H

#include "sound_effect.h"

namespace Controller {
class GameController;
};

namespace View {
class ReloadSound: public SoundEffect {
public:
    ReloadSound(
        Weak<Controller::GameController> controller,
        short_id_t player_id
    );

    ~ReloadSound() override = default;
};
};

#endif // CLIENT_GAME_SOUND_RELOAD_SOUND_H
