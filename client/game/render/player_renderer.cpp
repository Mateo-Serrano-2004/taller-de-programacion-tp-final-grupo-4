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

#include "controller/game_controller.h"

#include "asset/asset_manager.h"
#include "asset/font_id.h"
#include "asset/texture_id.h"

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
): View::Renderer(controller),
   background(controller) {
    auto controller_locked = controller.lock();
    game_state_manager = controller_locked->get_game_state_manager();
    font = asset_manager->generate_font("liberationsans", 16);
    background.set_background_color(0, 255, 255, 255);
    background.set_draw_background(true);
}

void View::PlayerRenderer::render() {
    background.render();
    auto camera = game_state_manager->get_camera();
    angle_t angle = 0;

    game_state_manager->call_function_on_players(
        [this, &angle] (std::map<short_id_t, Shared<View::RenderedPlayer>>& map) {
            if (map.empty()) return;
            Shared<View::RenderedPlayer> reference_player = nullptr;
            short_id_t reference_player_id = game_state_manager->get_reference_player_id();

            for (auto& pair : map) {
                if (pair.first == reference_player_id) {
                    reference_player = pair.second;
                } else {
                    pair.second->render();
                }
            }
            angle = reference_player->get_angle();
            reference_player->render();
        }
    );
    render_fov(angle, camera);
};
