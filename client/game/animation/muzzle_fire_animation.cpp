#include "muzzle_fire_animation.h"

#include <cstdint>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "asset/animation_id.h"
#include "controller/game_controller.h"
#include "handler/game_state_manager.h"
#include "model/rendered_player.h"
#include "render/camera.h"

void View::MuzzleFireAnimation::render_muzzle(Shared<View::RenderedPlayer> player) {
    auto camera = game_state_manager->get_camera_unsafe();
    SDL2pp::Point camera_view = camera.get_camera_view(player->get_position());
    int camera_view_x = camera_view.GetX();
    int camera_view_y = camera_view.GetY();

    SDL2pp::Rect fire_coords(camera_view_x - 16, camera_view_y - 32 - 10, 32, 32);
    SDL2pp::Point point_to_rotate(16, 32 + 10);

    renderer->Copy(*details.animation, get_frame(), fire_coords, player->get_angle(),
                   point_to_rotate);
}

View::MuzzleFireAnimation::MuzzleFireAnimation(Weak<Controller::GameController> controller,
                                               short_id_t player_id):
        View::Animation(controller, Model::AnimationID::MUZZLE_FIRE), player_id(player_id) {}

void View::MuzzleFireAnimation::render() {
    if (!ended) {
        auto player = game_state_manager->get_player_by_id_unsafe(player_id);
        if (player) {
            render_muzzle(player);
            step(frames_to_process);
        } else {
            ended = true;
        }
    }
}
