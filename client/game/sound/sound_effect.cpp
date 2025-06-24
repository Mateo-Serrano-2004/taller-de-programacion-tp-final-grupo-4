#include "sound_effect.h"

#include <algorithm>
#include <cmath>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"
#include "model/rendered_player.h"
#include "utils/enum_translator.h"

int View::SoundEffect::calculate_volume(int current_distance, int min_range, int max_range) {
    // Volume in range [0, 80]

    if (current_distance <= min_range) return 80;
    if (current_distance >= max_range) return 0;

    float t = (float) ((current_distance - min_range)) / (float) ((max_range - min_range));
    float cosine = std::cos(t * M_PI);
    float volume = 0.5f * (1 + cosine) * 80.0f;

    return static_cast<int>(volume);
}

void View::SoundEffect::update_volume() {
    auto camera_view = get_fixation().get_center();
    int dx = std::abs(camera_view.GetX() - position.GetX());
    int dy = std::abs(camera_view.GetY() - position.GetY());
    int distance = std::sqrt((dx * dx) + (dy * dy));
    mixer->SetVolume(channel, calculate_volume(distance, 100, 350));
}

View::SoundEffect::SoundEffect(
    Weak<Controller::BaseController> controller,
    Model::SoundID sound_id
): started(false), ended(false), channel(-1), mixer(nullptr),
   chunk(nullptr), controller(controller) {
    auto asset_manager = controller.lock()->get_asset_manager();
    mixer = asset_manager->get_mixer();
    chunk = asset_manager->get_sound(sound_id);
}

bool View::SoundEffect::is_playing() const {
    return started;
}

bool View::SoundEffect::has_ended() const {
    return ended;
}

void View::SoundEffect::set_position(const SDL2pp::Point& new_poisition) {
    position = new_poisition;
}

void View::SoundEffect::play() {
    if (!ended && !started && chunk) {
        channel = mixer->PlayChannel(-1, *chunk, 0);
        ended = (channel != -1);
    }
    if (!ended) {
        started = true;
        update_volume();
        ended = (mixer->IsChannelPlaying(channel));
    } else {
        channel = -1;
    }
}

void View::SoundEffect::end() {
    ended = true;
    started = false;
}

