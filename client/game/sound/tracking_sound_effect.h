#ifndef CLIENT_GAME_SOUND_TRACKING_SOUND_EFFECT_H
#define CLIENT_GAME_SOUND_TRACKING_SOUND_EFFECT_H

#include "asset/sound_id.h"
#include "common/weapon_id.h"

#include "distanced_sound_effect.h"
#include "sound_effect.h"

namespace SDL2pp {
class Mixer;
class Chunk;
};  // namespace SDL2pp

namespace Controller {
class GameController;
};

namespace View {
class RenderedPlayer;

class TrackingSoundEffect: public DistancedSoundEffect {
protected:
    Shared<RenderedPlayer> player;
    short_id_t player_id;

public:
    TrackingSoundEffect(Weak<Controller::GameController> controller, Model::SoundID sound_id,
                        short_id_t player_id);

    short_id_t get_player_id() const;

    void set_player(Shared<RenderedPlayer> new_player);

    void play() override;

    virtual ~TrackingSoundEffect() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_SOUND_TRACKING_SOUND_EFFECT_H
