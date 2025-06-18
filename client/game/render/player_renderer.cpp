#include "player_renderer.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>

#include <SDL2pp/Color.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>

#include "asset/asset_manager.h"
#include "asset/font_id.h"
#include "asset/texture_id.h"
#include "controller/game_controller.h"
#include "handler/game_state_manager.h"
#include "model/rendered_player.h"

#include "camera.h"

void View::PlayerRenderer::render_fov(angle_t angle, const Camera& camera) {
    auto viewport = camera.get_viewport();
    int viewport_width = viewport.GetX();
    int viewport_height = viewport.GetY();

    // Id del fov_texture
    auto fov_texture = asset_manager->get_texture(Model::TextureID::FOV);

    // Squared texture
    int fov_texture_size = fov_texture->GetWidth();

    int length_to_corners =
            std::sqrt((viewport_width * viewport_width) + (viewport_height * viewport_height)) / 2;

    renderer->Copy(*fov_texture,
                   SDL2pp::Rect((fov_texture_size - 2 * length_to_corners) / 2,
                                (fov_texture_size - 2 * length_to_corners) / 2,
                                2 * length_to_corners, 2 * length_to_corners),
                   SDL2pp::Rect((viewport_width - 2 * length_to_corners) / 2,
                                (viewport_height - 2 * length_to_corners) / 2,
                                2 * length_to_corners, 2 * length_to_corners),
                   angle);
}

SDL2pp::Rect View::PlayerRenderer::get_map_slice(Shared<SDL2pp::Texture> map,
                                                 const Camera& camera) {
    auto logical_width = renderer->GetLogicalWidth();
    auto logical_height = renderer->GetLogicalHeight();
    auto camera_x = camera.get_center().GetX() + 16;
    auto camera_y = camera.get_center().GetY() + 16;
    auto map_width = map->GetWidth();
    auto map_height = map->GetHeight();

    coord_t x = camera_x - (logical_width / 2);
    coord_t y = camera_y - (logical_height / 2);

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    coord_t w = std::max(0, std::min(logical_width, map_width - x));
    coord_t h = std::max(0, std::min(logical_height, map_height - y));

    return SDL2pp::Rect(x, y, w, h);
}

SDL2pp::Rect View::PlayerRenderer::get_viewport_slice(const SDL2pp::Rect map_slice,
                                                      const Camera& camera) {
    auto logical_width = renderer->GetLogicalWidth();
    auto logical_height = renderer->GetLogicalHeight();
    auto camera_x = camera.get_center().GetX() + 16;
    auto camera_y = camera.get_center().GetY() + 16;

    coord_t x = std::max(0, (logical_width / 2) - camera_x);
    coord_t y = std::max(0, (logical_height / 2) - camera_y);

    coord_t w = map_slice.GetW();
    coord_t h = map_slice.GetH();

    return SDL2pp::Rect(x, y, w, h);
}

void View::PlayerRenderer::render_map(const View::Camera& camera) {
    auto map = game_state_manager->get_map();
    if (!map)
        return;
    auto map_slice = get_map_slice(map, camera);
    auto viewport_slice = get_viewport_slice(map_slice, camera);
    renderer->Copy(*map, map_slice, viewport_slice);
}

View::PlayerRenderer::PlayerRenderer(Weak<Controller::GameController> controller):
        View::Renderer(controller) {
    auto controller_locked = controller.lock();
    game_state_manager = controller_locked->get_game_state_manager();
    font = asset_manager->generate_font("liberationsans", 16);
}

void View::PlayerRenderer::render() {
    auto camera = game_state_manager->get_camera();
    render_map(camera);
    bool render_ref_player = true;
    angle_t angle = 0;

    game_state_manager->call_function_on_players(
            [this, &angle,
             &render_ref_player](std::map<short_id_t, Shared<View::RenderedPlayer>>& map) {
                Shared<View::RenderedPlayer> reference_player =
                        game_state_manager->get_reference_player_unsafe();
                render_ref_player = (bool)reference_player;

                for (auto& pair: map) {
                    if (pair.second != reference_player)
                        pair.second->render();
                }

                if (render_ref_player) {
                    angle = reference_player->get_angle();
                    reference_player->render();
                }
            });
    if (render_ref_player)
        render_fov(angle, camera);
}
