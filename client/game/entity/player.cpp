#include "player.h"

#include <utility>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "common/model/player.h"

#include "render/player_render_context.h"

std::pair<uint16_t, uint16_t> View::Player::get_skin_piece() const {
    short_id_t skin_piece = player.get_skin_piece();
    uint16_t skin_row = skin_piece ? static_cast<uint16_t>((skin_piece - 1) / 2) : 0;
    uint16_t skin_column = static_cast<uint16_t>(skin_piece % 2);

    uint16_t skin_piece_x = skin_column * width;
    uint16_t skin_piece_y = skin_row * height;

    return std::make_pair(skin_piece_x, skin_piece_y);
}

View::Player::Player(Model::Player& player)
: RectEntity(0, 0, 32, 32), player(player) {
    position.set_x(player.get_position().get_x());
    position.set_y(player.get_position().get_y());
}

void View::Player::render(RenderContext& render_context) {
    // For sure this is a PlayerRenderContext
    auto& player_render_context = static_cast<View::PlayerRenderContext&>(render_context);

    // Everything needed for rendering a Player
    SDL2pp::Renderer& renderer = player_render_context.renderer;
    Model::TextureStorage& texture_storage = player_render_context.texture_storage;
    View::Camera& camera = player_render_context.camera;
    SDL2pp::Texture& texture = texture_storage.get_texture(player.get_skin_id());
    std::pair<uint16_t, uint16_t> skin_piece_coords = get_skin_piece();
    angle_t angle = player.get_angle();

    // Get the view from the camera
    length_t viewport_width = camera.get_viewport_width();
    length_t viewport_height = camera.get_viewport_height();
    SDL2pp::Point camera_view = camera.get_camera_view(position);
    int camera_view_x = camera_view.GetX();
    int camera_view_y = camera_view.GetY();

    // Skip rendering if the player is outside the viewport
    if (camera_view_x >= viewport_width ||
        camera_view_y >= viewport_height ||
        camera_view_x + viewport_width <= 0 ||
        camera_view_y + viewport_height <= 0) {
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
        skin_piece_coords.first,
        skin_piece_coords.second,
        width,
        height
    );

    SDL2pp::Point top_left_corner(
        camera_view_x - (width / 2),
        camera_view_y - (height / 2)
    );

    renderer.Copy(
        texture,
        skin_rect,
        top_left_corner,
        angle,
        SDL2pp::NullOpt
    );
}
