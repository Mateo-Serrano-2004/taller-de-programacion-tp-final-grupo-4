#include "distanced_sound_effect.h"

#include <algorithm>
#include <cmath>

#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Point.hh>

#include "controller/game_controller.h"

int View::DistancedSoundEffect::calculate_volume(int current_distance, int min_range,
                                                 int max_range) {
    // Volume in range [0, 80]

    if (current_distance <= min_range)
        return 80;
    if (current_distance >= max_range)
        return 0;

    float t = (float)((current_distance - min_range)) / (float)((max_range - min_range));
    float cosine = std::cos(t * M_PI);
    float volume = 0.5f * (1 + cosine) * 80.0f;

    return static_cast<int>(volume);
}

void View::DistancedSoundEffect::update_volume() {
    auto camera_view = get_fixation().get_center();
    int dx = std::abs(camera_view.GetX() - position.GetX());
    int dy = std::abs(camera_view.GetY() - position.GetY());
    int distance = std::sqrt((dx * dx) + (dy * dy));
    set_volume(calculate_volume(distance, 100, 350));
}

void View::DistancedSoundEffect::set_position(const SDL2pp::Point& new_poisition) {
    position = new_poisition;
}

void View::DistancedSoundEffect::play() {
    SoundEffect::play();
    if (!ended)
        update_volume();
}

View::DistancedSoundEffect::DistancedSoundEffect(Weak<Controller::BaseController> controller,
                                                 Model::SoundID sound_id):
        View::SoundEffect(controller, sound_id) {}
