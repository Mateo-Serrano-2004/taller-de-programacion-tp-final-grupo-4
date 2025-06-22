#ifndef CLIENT_GAME_SOUND_EFFECT_H
#define CLIENT_GAME_SOUND_EFFECT_H

#include "asset/sound_id.h"
#include "common/definitions.h"
#include "interface/fixed.h"

namespace SDL2pp {
class Mixer;
class Chunk;
};

namespace View {
class SoundEffect: public Fixed {
protected:
    Shared<SDL2pp::Mixer> mixer;
    Shared<SDL2pp::Chunk> chunk;

public:
    SoundEffect(Model::SoundID id);
    ~SoundEffect() override = default;
};
};

#endif // CLIENT_GAME_SOUND_EFFECT_H
