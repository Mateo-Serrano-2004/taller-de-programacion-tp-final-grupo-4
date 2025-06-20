#include "player_renderer.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>

#include <SDL2pp/Color.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>

#include "animation/muzzle_fire_animation.h"
#include "animation/progress_bar_animation.h"
#include "animation/winner_team_message_animation.h"
#include "asset/asset_manager.h"
#include "asset/font_id.h"
#include "asset/texture_id.h"
#include "controller/game_controller.h"
#include "handler/game_state_manager.h"
#include "model/game_state.h"
#include "model/rendered_player.h"

#include "camera.h"

void View::PlayerRenderer::render_winner_message(const Model::GameState& game_state, uint8_t frames) {
    if (game_state.winner_message) {
        game_state.winner_message->step(frames);
    }
}

void View::PlayerRenderer::render_defusing_progress(const Model::GameState& game_state) {
    if (game_state.bomb_defusing) {
        game_state.bomb_defusing->progress(game_state.defusing_progress);
    }
}

void View::PlayerRenderer::render_fov(const Model::GameState& game_state) {
    auto viewport = game_state.camera.get_viewport();
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
                   game_state.get_reference_player()->get_angle());
}

void View::PlayerRenderer::render_muzzle_fires(const Model::GameState& game_state, uint8_t frames) {
    auto camera = game_state.camera;
    for (auto& animation: game_state.fires) {
        auto player = game_state.get_player_by_id(animation->get_player_id());
        if (!player) {
            animation->end();
            continue;
        }
        animation->set_player(player);
        animation->step(frames);
    }
}

void View::PlayerRenderer::render_bomb(const Model::GameState& game_state) {
    if (game_state.bomb_position.has_value()) {
        auto point = game_state.camera.get_camera_view(game_state.bomb_position.value());
        renderer->Copy(
            *bomb_texture,
            SDL2pp::NullOpt,
            point
        );
    }
}

bool View::PlayerRenderer::render_players(const Model::GameState& game_state) {
    auto reference_player = game_state.get_reference_player();
    bool render_ref_player = (bool)reference_player;
    auto camera = game_state.camera;

    for (auto& [id, p]: game_state.players) {
        if (!render_ref_player || id != reference_player->get_id()) {
            p->fix(camera);
            p->render();
        }
    }

    if (render_ref_player) {
        reference_player->fix(camera);
        reference_player->render();
    }

    return render_ref_player;
}

SDL2pp::Rect View::PlayerRenderer::get_map_slice(Shared<SDL2pp::Texture> map,
                                                 const View::Camera& camera) {
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

SDL2pp::Rect View::PlayerRenderer::get_viewport_slice(const SDL2pp::Rect& map_slice,
                                                      const View::Camera& camera) {
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

void View::PlayerRenderer::render_map(const Model::GameState& game_state) {
    auto map = game_state.map;
    auto camera = game_state.camera;
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
    bomb_texture = asset_manager->get_texture(Model::TextureID::SPRITE_BOMB);
}

void View::PlayerRenderer::render(const Model::GameState& game_state, uint8_t frames) {
    render_map(game_state);
    auto render_ref_player = render_players(game_state);
    render_bomb(game_state);
    render_muzzle_fires(game_state, frames);
    if (render_ref_player)
        render_fov(game_state);
    render_defusing_progress(game_state);
    render_winner_message(game_state, frames);
}
