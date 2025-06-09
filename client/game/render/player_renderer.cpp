#include "player_renderer.h"

#include <map>
#include <cmath>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Font.hh>

#include "camera.h"

#include "controller/game_controller.h"

#include "asset/asset_manager.h"
#include "asset/font_id.h"
#include "asset/texture_id.h"

#include "handler/game_state_manager.h"

#include "model/rendered_player.h"

SDL2pp::Point View::PlayerRenderer::get_sprite_top_left_corner(short_id_t sprite_piece) {
    uint16_t sprite_row = sprite_piece ? static_cast<uint16_t>((sprite_piece - 1) / 2) : 0;
    uint16_t sprite_column = static_cast<uint16_t>(sprite_piece % 2);

    uint16_t sprite_piece_x = sprite_column * 32;
    uint16_t sprite_piece_y = sprite_row * 32;

    return SDL2pp::Point(sprite_piece_x, sprite_piece_y);
}

void View::PlayerRenderer::render_weapon(const SDL2pp::Point& player_center,
                                         angle_t player_angle,
                                         Model::TextureID texture_id) {
    Shared<SDL2pp::Texture> weapon_texture = asset_manager->get_texture(texture_id);

    SDL2pp::Rect weapon_coords(player_center.GetX() - 16, player_center.GetY() - 32, 32, 32);
    SDL2pp::Point point_to_rotate(16, 32);

    renderer->Copy(*weapon_texture, SDL2pp::NullOpt, weapon_coords, player_angle, point_to_rotate);
}

void View::PlayerRenderer::render_name(const SDL2pp::Point& player_center,
                                       const std::string& player_name) {
    Shared<SDL2pp::Texture> text = asset_manager->apply_font_to_text(
        font,
        player_name,
        SDL2pp::Color(255, 255, 255, 255)
    );
    renderer->Copy(
        *text,
        SDL2pp::NullOpt,
        SDL2pp::Rect(
            player_center.GetX() - (text->GetWidth()) / 2,
            player_center.GetY() - 17 - text->GetHeight(),
            text->GetWidth(), text->GetHeight()
        )
    );
}

void View::PlayerRenderer::render_player(View::Camera& camera, Shared<View::RenderedPlayer>& player) {
    Shared<SDL2pp::Texture> texture = asset_manager->get_texture((Model::TextureID) player->get_sprite_id());
    SDL2pp::Point sprite_top_left_corner = get_sprite_top_left_corner(player->get_sprite_piece());
    angle_t angle = player->get_angle();

    // Get the view from the camera
    coord_t viewport_width = camera.get_viewport_width();
    coord_t viewport_height = camera.get_viewport_height();

    SDL2pp::Point camera_view = camera.get_camera_view(player->get_position());
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

    SDL2pp::Rect sprite_rect(
        sprite_top_left_corner.GetX(),
        sprite_top_left_corner.GetY(),
        32,
        32
    );

    SDL2pp::Point top_left_corner(
        camera_view_x - 16,
        camera_view_y - 16
    );

    renderer->Copy(
        *texture,
        sprite_rect,
        top_left_corner,
        angle,
        SDL2pp::NullOpt
    );

    render_weapon(camera_view, angle, player->get_weapon_sprite_id());
    render_name(camera_view, player->get_name());
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
): View::Renderer(controller), background(controller) {
    auto controller_locked = controller.lock();
    game_state_manager = controller_locked->get_game_state_manager();
    font = asset_manager->generate_font("liberationsans", 16);
    background.set_background_color(0, 255, 255, 255);
    background.set_draw_background(true);
}

void View::PlayerRenderer::render() {
    background.render();
    auto camera = game_state_manager->get_camera();

    game_state_manager->call_function_on_players(
        [this, &camera] (std::map<short_id_t, Shared<View::RenderedPlayer>>& map) {
            Shared<View::RenderedPlayer> reference_player = nullptr;
            short_id_t reference_player_id = game_state_manager->get_reference_player_id();

            for (auto& pair : map) {
                if (pair.first == reference_player_id) {
                    reference_player = pair.second;
                } else {
                    render_player(camera, pair.second);
                }
            }

            render_fov(reference_player->get_angle());
            render_player(camera, reference_player);
        }
    );
};
