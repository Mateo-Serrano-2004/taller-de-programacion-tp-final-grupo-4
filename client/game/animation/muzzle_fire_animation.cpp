#include "muzzle_fire_animation.h"

#include <cstdint>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "asset/animation_id.h"
#include "common/model/weapon.h"
#include "common/weapon_id.h"
#include "controller/game_controller.h"
#include "handler/game_state_manager.h"
#include "model/rendered_player.h"
#include "render/camera.h"

int View::MuzzleFireAnimation::get_fire_distance() {
    Model::WeaponID weapon_id = player->get_current_weapon()->get_weapon_id();
    switch (weapon_id) {
        case Model::WeaponID::AK47:
            return 20;
        case Model::WeaponID::GLOCK:
            return 12;
        case Model::WeaponID::M3:
            return 16;
        case Model::WeaponID::AWP:
            return 25;
        default:
            return 0;
    }
}

int View::MuzzleFireAnimation::get_frame_size() { return 32; }

SDL2pp::Rect View::MuzzleFireAnimation::get_dsrect() {
    SDL2pp::Point camera_view = player->get_fixation().get_camera_view(player->get_position());
    int camera_view_x = camera_view.GetX();
    int camera_view_y = camera_view.GetY();
    auto fire_distance = get_fire_distance();
    return SDL2pp::Rect(camera_view_x - 16, camera_view_y - 32 - fire_distance, 32, 32);
}

angle_t View::MuzzleFireAnimation::get_angle() { return player->get_angle(); }

SDL2pp::Point View::MuzzleFireAnimation::get_rpoint() {
    auto fire_distance = get_fire_distance();
    return SDL2pp::Point(16, 32 + fire_distance);
}

View::MuzzleFireAnimation::MuzzleFireAnimation(Weak<Controller::GameController> controller,
                                               short_id_t player_id):
        View::IterativeAnimation(controller, Model::AnimationID::MUZZLE_FIRE),
        player_id(player_id) {}

short_id_t View::MuzzleFireAnimation::get_player_id() const { return player_id; }

void View::MuzzleFireAnimation::set_player(Shared<RenderedPlayer> new_player) {
    player = new_player;
}

bool View::MuzzleFireAnimation::has_ended() const { return ended && player; }
