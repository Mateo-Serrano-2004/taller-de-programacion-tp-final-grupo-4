#include "muzzle_fire_animation.h"

#include <cstdint>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>

#include "common/weapon_id.h"
#include "common/model/weapon.h"

#include "controller/game_controller.h"

#include "handler/game_state_manager.h"

#include "asset/animation_id.h"

#include "model/rendered_player.h"

#include "render/camera.h"

int View::MuzzleFireAnimation::get_fire_distance() {
    Model::WeaponID weapon_id = player->get_current_weapon()->get_weapon_id();
    switch (weapon_id) {
        case Model::WeaponID::AK47:
            return 20;
        case Model::WeaponID::GLOCK:
            return 16;
        case Model::WeaponID::M3:
            return 18;
        case Model::WeaponID::AWP:
            return 25;
    }
    return 0;
}

void View::MuzzleFireAnimation::render_muzzle() {
    SDL2pp::Point camera_view = camera.get_camera_view(player->get_position());
    int camera_view_x = camera_view.GetX();
    int camera_view_y = camera_view.GetY();
    auto fire_distance = get_fire_distance();

    SDL2pp::Rect fire_coords(camera_view_x - 16, camera_view_y - 32 - fire_distance, 32, 32);
    SDL2pp::Point point_to_rotate(16, 32 + fire_distance);

    renderer->Copy(
        *details.animation,
        get_frame(),
        fire_coords,
        player->get_angle(),
        point_to_rotate
    );
}

View::MuzzleFireAnimation::MuzzleFireAnimation(Weak<Controller::GameController> controller,
                                               short_id_t player_id):
        View::Animation(controller, Model::AnimationID::MUZZLE_FIRE), player_id(player_id) {}

short_id_t View::MuzzleFireAnimation::get_player_id() const { return player_id; }

void View::MuzzleFireAnimation::set_camera(const Camera& new_camera) {
    camera = new_camera;
}

void View::MuzzleFireAnimation::set_player(Shared<RenderedPlayer> new_player) {
    player = new_player;
}

void View::MuzzleFireAnimation::end() {
    ended = true;
}

void View::MuzzleFireAnimation::render() {
    if (!ended) {
        if (player) {
            render_muzzle();
            step(frames_to_process);
        } else {
            ended = true;
        }
    }
}
