#ifndef CLIENT_GAME_SOUND_SOUND_EFFECT_H
#define CLIENT_GAME_SOUND_SOUND_EFFECT_H

#include <SDL2pp/Point.hh>

#include "asset/sound_id.h"
#include "common/definitions.h"
#include "interface/fixed.h"

namespace SDL2pp {
class Mixer;
class Chunk;
};

namespace Controller {
class BaseController;
};

namespace View {
class SoundEffect: public Fixed {
protected:
    bool started;
    bool ended;
    int channel;
    SDL2pp::Point position;
    SDL2pp::Mixer* mixer;
    Shared<SDL2pp::Chunk> chunk;
    Weak<Controller::BaseController> controller;

    int calculate_volume(int current_distance, int min_range, int max_range);
    void update_volume();

public:
    SoundEffect(
        Weak<Controller::BaseController> controller,
        Model::SoundID sound_id
    );

    bool is_playing() const;
    bool has_ended() const;

    void set_position(const SDL2pp::Point& new_poisition);
    virtual void play();
    void end();

    virtual ~SoundEffect() = default;
};
};

#endif // CLIENT_GAME_SOUND_SOUND_EFFECT_H
