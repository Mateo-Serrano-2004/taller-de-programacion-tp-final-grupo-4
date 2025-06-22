#ifndef CLIENT_GAME_SOUND_EFFECT_H
#define CLIENT_GAME_SOUND_EFFECT_H

#include "asset/sound_id.h"
#include "common/definitions.h"
#include "common/weapon_id.h"

namespace SDL2pp {
class Mixer;
class Chunk;
};

namespace Controller {
class GameController;
};

namespace View {
class RenderedPlayer;

class SoundEffect {
protected:
    bool started;
    bool ended;
    int channel;
    Shared<RenderedPlayer> player;
    SDL2pp::Mixer* mixer;
    Shared<SDL2pp::Chunk> chunk;
    Weak<Controller::GameController> controller;
    short_id_t player_id;

    int calculate_volume(int current_distance, int min_range, int max_range);
    void update_volume();

public:
    SoundEffect(
        Weak<Controller::GameController> controller,
        short_id_t player_id,
        Model::WeaponID weapon_id
    );

    bool is_playing() const;
    bool has_ended() const;
    short_id_t get_player_id() const;

    void set_player(Shared<RenderedPlayer> new_player);
    void play();
    void end();

    ~SoundEffect() = default;
};
};

#endif // CLIENT_GAME_SOUND_EFFECT_H
