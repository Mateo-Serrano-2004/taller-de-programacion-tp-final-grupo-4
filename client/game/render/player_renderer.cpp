#include "player_renderer.h"

#include <map>
#include <cmath>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "common/model/player.h"
#include "common/texture_id.h"

#include "camera.h"

#include "controller/game_controller.h"
#include "asset/asset_manager.h"
#include "common/texture_id.h"
#include "handler/game_state_manager.h"

SDL2pp::Point View::PlayerRenderer::get_skin_top_left_corner(short_id_t skin_piece) {
    uint16_t skin_row = skin_piece ? static_cast<uint16_t>((skin_piece - 1) / 2) : 0;
    uint16_t skin_column = static_cast<uint16_t>(skin_piece % 2);

    uint16_t skin_piece_x = skin_column * 32;
    uint16_t skin_piece_y = skin_row * 32;

    return SDL2pp::Point(skin_piece_x, skin_piece_y);
}

void View::PlayerRenderer::render_player(View::Camera& camera, Model::Player& player) {
    Shared<SDL2pp::Texture> texture = asset_manager->get_texture((Model::TextureID) player.get_skin_id());
    SDL2pp::Point skin_top_left_corner = get_skin_top_left_corner(player.get_skin_piece());
    angle_t angle = player.get_angle();

    // Get the view from the camera
    coord_t viewport_width = camera.get_viewport_width();
    coord_t viewport_height = camera.get_viewport_height();

    SDL2pp::Point camera_view = camera.get_camera_view(player.get_position());
    int camera_view_x = camera_view.GetX();
    int camera_view_y = camera_view.GetY();

    // Skip rendering if the player is outside the viewport
    if (camera_view_x >= viewport_width + 15 ||
        camera_view_y >= viewport_height + 15 ||
        camera_view_x + 15 <= 0 ||
        camera_view_y + 15 <= 0) {
        return;
    }

    /*
        Camera is centered on the middle of a texture,
        but SDL2pp::Renderer::Copy takes the top-left corner
        of the texture as the origin point.
        So we need to adjust the camera view coordinates
        to account for the texture's width and height.
    */

    SDL2pp::Rect skin_rect(
        skin_top_left_corner.GetX(),
        skin_top_left_corner.GetY(),
        32,
        32
    );

    SDL2pp::Point top_left_corner(
        camera_view_x - 16,
        camera_view_y - 16
    );

    renderer->Copy(
        *texture,
        skin_rect,
        top_left_corner,
        angle,
        SDL2pp::NullOpt
    );
}

void View::PlayerRenderer::render_fov(angle_t angle) {
    auto viewport = game_state_manager->get_camera().get_viewport();
    int viewport_width = viewport.GetX();
    int viewport_height = viewport.GetY();

    // Id del fov_texture
    auto fov_texture = asset_manager->get_texture(Model::TextureID::FOV);

    // Squared texture
    int fov_texture_size = fov_texture->GetWidth();

    int length_to_corners = std::sqrt(
        (viewport_width * viewport_width) + (viewport_height * viewport_height)
    ) / 2;

    renderer->Copy(
        *fov_texture,
        SDL2pp::Rect(
            (fov_texture_size - 2 * length_to_corners) / 2,
            (fov_texture_size - 2 * length_to_corners) / 2,
            2 * length_to_corners,
            2 * length_to_corners
        ),
        SDL2pp::Rect(
            (viewport_width - 2 * length_to_corners) / 2,
            (viewport_height - 2 * length_to_corners) / 2,
            2 * length_to_corners,
            2 * length_to_corners
        ),
        angle
    );
}

View::PlayerRenderer::PlayerRenderer(
    Weak<Controller::GameController> controller
): View::Renderer(controller) {
    auto controller_locked = controller.lock();
    game_state_manager = controller_locked->get_game_state_manager();
}

void View::PlayerRenderer::render() {
    auto camera = game_state_manager->get_camera();

    game_state_manager->call_function_on_players(
        [this, &camera] (std::map<short_id_t, Model::Player>& map) {
            Model::Player* reference_player = nullptr;
            short_id_t reference_player_id = game_state_manager->get_reference_player_id();

            for (auto& pair : map) {
                if (pair.first == reference_player_id) {
                    reference_player = &pair.second;
                } else {
                    render_player(camera, pair.second);
                }
            }

            render_player(camera, *reference_player);
            render_fov(reference_player->get_angle());
        }
    );
};
