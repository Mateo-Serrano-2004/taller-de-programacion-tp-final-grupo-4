#include "tracking_sound_effect.h"

#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>

#include "controller/game_controller.h"
#include "model/rendered_player.h"

View::TrackingSoundEffect::TrackingSoundEffect(Weak<Controller::GameController> controller,
                                               Model::SoundID sound_id, short_id_t player_id):
        View::DistancedSoundEffect(controller, sound_id), player_id(player_id) {}

short_id_t View::TrackingSoundEffect::get_player_id() const { return player_id; }

void View::TrackingSoundEffect::set_player(Shared<View::RenderedPlayer> new_player) {
    player = new_player;
}

void View::TrackingSoundEffect::play() {
    if (player) {
        auto new_pos = player->get_position();
        set_position(SDL2pp::Point(new_pos.get_x(), new_pos.get_y()));
        fix(player->get_fixation());
    }
    View::DistancedSoundEffect::play();
}
