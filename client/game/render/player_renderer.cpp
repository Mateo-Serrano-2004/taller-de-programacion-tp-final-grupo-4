#include "player_renderer.h"

#include <map>
#include <list>
#include <cmath>
#include <cstdint>
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

#include "controller/game_controller.h"

#include "handler/game_state_manager.h"

#include "asset/asset_manager.h"
#include "asset/font_id.h"
#include "asset/texture_id.h"

#include "model/rendered_player.h"

#include "animation/muzzle_fire_animation.h"

#include "camera.h"
#include "render_context.h"
#include "full_render_context.h"

void View::PlayerRenderer::render_fov(const Model::FullRenderContext& render_context) {
    auto viewport = render_context.camera.get_viewport();
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
                   render_context.ref_player->get_angle());
}

void View::PlayerRenderer::render_muzzle_fires(const Model::FullRenderContext& render_context, uint8_t frames) {
    auto camera = render_context.camera;
    for (auto& animation: render_context.fires) {
        auto player = render_context.players.find(animation->get_player_id());
        if (player == render_context.players.end()) {
            animation->end();
            continue;
        }
        animation->set_frames_to_process(frames);
        animation->set_camera(camera);
        animation->set_player(player->second);
        animation->render();
    }
}

bool View::PlayerRenderer::render_players(const Model::FullRenderContext& render_context) {
    auto reference_player = render_context.ref_player;
    bool render_ref_player = (bool) reference_player;
    auto camera = render_context.camera;

    for (auto& [id, p]: render_context.players) {
        if (id != reference_player->get_id()) {
            p->set_camera(camera);
            p->render();
        }
    }

    if (render_ref_player) {
        reference_player->set_camera(camera);
        reference_player->render();
    }

    return render_ref_player;
}

SDL2pp::Rect View::PlayerRenderer::get_map_slice(
    Shared<SDL2pp::Texture> map,
    const View::Camera& camera
) {
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

SDL2pp::Rect View::PlayerRenderer::get_viewport_slice(
    const SDL2pp::Rect& map_slice,
    const View::Camera& camera
) {
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

void View::PlayerRenderer::render_map(const Model::FullRenderContext& render_context) {
    auto map = render_context.map;
    auto camera = render_context.camera;
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

void View::PlayerRenderer::render(uint8_t frames) {
    Model::FullRenderContext render_context = game_state_manager->get_full_render_context();

    render_map(render_context);
    auto render_ref_player = render_players(render_context);
    render_muzzle_fires(render_context, frames);
    if (render_ref_player) render_fov(render_context);
};
