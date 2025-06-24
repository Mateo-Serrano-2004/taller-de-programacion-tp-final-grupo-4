#include "bomb_explosion_animation.h"

#include "asset/texture_id.h"
#include "controller/game_controller.h"
#include "render/camera.h"

int View::BombExplosionAnimation::get_frame_size() { return 64; }

SDL2pp::Rect View::BombExplosionAnimation::get_dsrect() {
    auto camera = get_fixation();
    auto fixed_pos = camera.get_camera_view(bomb_position);
    return SDL2pp::Rect(fixed_pos.GetX() - 32, fixed_pos.GetY() - 32, 64, 64);
}

angle_t View::BombExplosionAnimation::get_angle() { return 0; }

SDL2pp::Point View::BombExplosionAnimation::get_rpoint() {
    auto camera = get_fixation();
    return camera.get_camera_view(bomb_position);
}

View::BombExplosionAnimation::BombExplosionAnimation(Weak<Controller::GameController> controller,
                                                     const SDL2pp::Point& bomb_position):
        View::IterativeAnimation(controller, Model::AnimationID::BOMB_EXPLOSION),
        Fixed(),
        bomb_position(bomb_position) {}
