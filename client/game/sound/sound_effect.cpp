#include "sound_effect.h"

#include <algorithm>
#include <cmath>

#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"
#include "model/rendered_player.h"
#include "utils/enum_translator.h"

View::SoundEffect::SoundEffect(Weak<Controller::BaseController> controller,
                               Model::SoundID sound_id):
        started(false),
        ended(false),
        channel(-1),
        mixer(nullptr),
        chunk(nullptr),
        controller(controller) {
    auto asset_manager = controller.lock()->get_asset_manager();
    mixer = asset_manager->get_mixer();
    chunk = asset_manager->get_sound(sound_id);

    // Max by default
    set_volume(80);
}

bool View::SoundEffect::is_playing() const { return started; }

bool View::SoundEffect::has_ended() const { return ended; }

void View::SoundEffect::set_volume(int new_volume) { mixer->SetVolume(channel, new_volume); }

void View::SoundEffect::play() {
    if (!ended && !started && chunk) {
        channel = mixer->PlayChannel(-1, *chunk, 0);
        ended = (channel != -1);
    }
    if (!ended) {
        started = true;
        ended = (mixer->IsChannelPlaying(channel));
    } else {
        channel = -1;
    }
}

void View::SoundEffect::end() {
    ended = true;
    started = false;
}
