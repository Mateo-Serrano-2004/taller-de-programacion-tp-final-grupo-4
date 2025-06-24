#ifndef CLIENT_GAME_SOUND_SOUND_EFFECT_H
#define CLIENT_GAME_SOUND_SOUND_EFFECT_H

#include <SDL2pp/Point.hh>

#include "asset/sound_id.h"
#include "common/definitions.h"

namespace SDL2pp {
class Mixer;
class Chunk;
};  // namespace SDL2pp

namespace Controller {
class BaseController;
};

namespace View {
class SoundEffect {
protected:
    bool started;
    bool ended;
    int channel;
    SDL2pp::Mixer* mixer;
    Shared<SDL2pp::Chunk> chunk;
    Weak<Controller::BaseController> controller;

public:
    SoundEffect(Weak<Controller::BaseController> controller, Model::SoundID sound_id);

    bool is_playing() const;
    bool has_ended() const;
    void set_volume(int new_volume);

    virtual void play();
    void end();

    virtual ~SoundEffect() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_SOUND_SOUND_EFFECT_H
