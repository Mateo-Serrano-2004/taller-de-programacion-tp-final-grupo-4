#include "player_renderer.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
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
#include "sound/tracking_sound_effect.h"

#include "camera.h"

void View::PlayerRenderer::render_fov(const Model::GameState& game_state) {
    angle_t angle = 0;
    auto ref_player = game_state.get_reference_player();
    if (!ref_player->get_health()) {
        ref_player = game_state.get_any_player_alive_by_team(ref_player->get_team());
    }
    if (!ref_player)
        return;
    angle = ref_player->get_angle();

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
                   angle);
}

void View::PlayerRenderer::render_bomb(const Model::GameState& game_state) {
    if (game_state.bomb_position.has_value()) {
        auto point = game_state.camera.get_camera_view(game_state.bomb_position.value());
        point.SetX(point.GetX() - (bomb_texture->GetWidth() / 2));
        point.SetY(point.GetY() - (bomb_texture->GetHeight() / 2));
        renderer->Copy(*bomb_texture, SDL2pp::NullOpt, point);
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

View::PlayerRenderer::PlayerRenderer(Weak<Controller::GameController> controller):
        View::Renderer(controller), map_renderer(controller), weapon_renderer(controller) {
    auto controller_locked = controller.lock();
    game_state_manager = controller_locked->get_game_state_manager();
    bomb_texture = asset_manager->get_texture(Model::TextureID::SPRITE_BOMB);
}

void View::PlayerRenderer::render(const Model::GameState& game_state, uint8_t frames) {
    map_renderer.render_map(game_state);
    weapon_renderer.render_weapons(game_state);
    auto render_ref_player = render_players(game_state);
    render_bomb(game_state);
    animation_renderer.render_muzzle_fires(game_state, frames);
    sound_player.play(game_state);
    if (render_ref_player)
        render_fov(game_state);
    animation_renderer.render_explosion(game_state, frames);
    animation_renderer.render_progress_bar(game_state);
    animation_renderer.render_winner_message(game_state, frames);
}
