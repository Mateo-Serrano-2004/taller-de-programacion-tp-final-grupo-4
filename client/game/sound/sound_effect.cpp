#include "sound_effect.h"

#include <cmath>
#include <iostream>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>

#include "asset/asset_manager.h"
#include "controller/game_controller.h"
#include "model/rendered_player.h"
#include "utils/enum_translator.h"

int View::SoundEffect::calculate_volume(int current_distance, int min_range, int max_range) {
    // Volume in range [0, 128]

    if (current_distance <= min_range) return 128;
    if (current_distance >= max_range) return 0;

    int t = (current_distance - min_range) / (max_range - min_range);
    float cosine = std::cos(t * M_PI);
    float volume = 0.5f * (1 + cosine) * 128.0f;

    return static_cast<int>(volume);
}

void View::SoundEffect::update_volume() {
    auto position = player->get_position();
    auto camera_view = player->get_fixation().get_center();
    int dx = std::abs(camera_view.GetX() - position.get_x());
    int dy = std::abs(camera_view.GetX() - position.get_x());
    int distance = std::sqrt((dx * dx) + (dy * dy));
    mixer->SetVolume(channel, calculate_volume(distance, 100, 350));
}

View::SoundEffect::SoundEffect(
    Weak<Controller::GameController> controller,
    short_id_t player_id,
    Model::WeaponID weapon_id
): started(false), ended(false), channel(-1), mixer(nullptr),
   controller(controller), player_id(player_id) {
    auto asset_manager = controller.lock()->get_asset_manager();
    mixer = asset_manager->get_mixer();
    chunk = asset_manager->get_sound(Model::EnumTranslator::get_sound_from_weapon(weapon_id));
}

bool View::SoundEffect::is_playing() const {
    return started;
}

bool View::SoundEffect::has_ended() const {
    return ended;
}

short_id_t View::SoundEffect::get_player_id() const {
    return player_id;
}

void View::SoundEffect::set_player(Shared<View::RenderedPlayer> new_player) {
    player = new_player;
}

void View::SoundEffect::play() {
    if (!started && chunk) {
        channel = mixer->PlayChannel(-1, *chunk, 0);
    }
    update_volume();
    ended = (mixer->IsChannelPlaying(channel));
}

void View::SoundEffect::end() {
    ended = true;
    started = false;
}
