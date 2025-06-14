#include "player_renderer.h"

#include <map>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Font.hh>

#include "common/team.h"

#include "controller/game_controller.h"

#include "asset/asset_manager.h"
#include "asset/font_id.h"
#include "asset/texture_id.h"

#include "handler/game_state_manager.h"

#include "model/rendered_player.h"

#include "camera.h"

SDL2pp::Point View::PlayerRenderer::get_sprite_top_left_corner(short_id_t sprite_piece) {
    uint16_t sprite_row = sprite_piece ? static_cast<uint16_t>(sprite_piece / 2) : 0;
    uint16_t sprite_column = static_cast<uint16_t>(sprite_piece % 2);

    uint16_t sprite_piece_x = sprite_column * 32;
    uint16_t sprite_piece_y = sprite_row * 32;

    return SDL2pp::Point(sprite_piece_x, sprite_piece_y);
}

void View::PlayerRenderer::set_player_to_be_rendered(
    Shared<View::RenderedPlayer> player,
    const SDL2pp::Point& camera_view,
    const SDL2pp::Point& player_display_size
) {
    SDL2pp::Point sprite_top_left_corner = get_sprite_top_left_corner(player->get_sprite_piece());
    angle_t angle = player->get_angle();    

    /*
        Camera is centered on the middle of a texture,
        but SDL2pp::Renderer::Copy takes the top-left corner
        of the texture as the origin point.
        So we need to adjust the camera view coordinates
        to account for the texture's width and height.
    */

    SDL2pp::Rect sprite_slice(
        sprite_top_left_corner.GetX(),
        sprite_top_left_corner.GetY(),
        32,
        32
    );

    game_sprites.emplace_back(controller);
    auto player_pane = &game_sprites.back();
    background.add_child(player_pane);

    player_pane->set_draw_texture(true);

    player_pane->set_texture(player->get_sprite_id());
    player_pane->set_texture_slice(sprite_slice);

    player_pane->set_angle(angle);

    SDL2pp::Point top_left_corner(
        camera_view.GetX() - (player_display_size.GetX() / 2),
        camera_view.GetY() - (player_display_size.GetY() / 2)
    );

    player_pane->set_position(top_left_corner);
    player_pane->set_size(player_display_size);
}

void View::PlayerRenderer::set_weapon_to_be_rendered(
    Shared<View::RenderedPlayer> player,
    const SDL2pp::Point& camera_view,
    const SDL2pp::Point& player_display_size
) {
    SDL2pp::Point position(
        camera_view.GetX() - (player_display_size.GetX() / 2),
        camera_view.GetY() - player_display_size.GetY()
    );
    SDL2pp::Point size(
        player_display_size.GetX(),
        player_display_size.GetY()
    );
    SDL2pp::Point rotation_point(
        (player_display_size.GetX() / 2),
        player_display_size.GetY()
    );

    game_sprites.emplace_back(controller);
    auto weapon_sprite = &game_sprites.back();
    background.add_child(weapon_sprite);

    weapon_sprite->set_draw_texture(true);

    weapon_sprite->set_texture(
        translator.get_texture_from_weapon(
            player->get_current_weapon()->get_weapon_id()
        )
    );
    weapon_sprite->set_angle(player->get_angle());
    weapon_sprite->set_rotation_point(rotation_point);

    weapon_sprite->set_size(size);
    weapon_sprite->set_position(position);
}

void View::PlayerRenderer::set_name_to_be_rendered(
    Shared<View::RenderedPlayer> player,
    const SDL2pp::Point& camera_view,
    const SDL2pp::Point& player_display_size
) {
    Model::TeamID team = player->get_team();
    SDL2pp::Color name_color = (team == Model::TeamID::CT) ?
        SDL2pp::Color(0, 0, 255, 255) :
        SDL2pp::Color(255, 0, 0, 255);
    Shared<SDL2pp::Texture> text = asset_manager->apply_font_to_text(
        font,
        player->get_name(),
        name_color
    );
    SDL2pp::Point position(
        camera_view.GetX() - (text->GetWidth()) / 2,
        camera_view.GetY() - (player_display_size.GetY() / 2) - text->GetHeight()
    );

    game_sprites.emplace_back(controller);
    auto name = &game_sprites.back();
    background.add_child(name);

    name->set_draw_texture(true);
    name->set_texture(text);

    name->set_position(position);
    name->set_size(text->GetSize());
}

void View::PlayerRenderer::load_player(View::Camera& camera, Shared<View::RenderedPlayer>& player) {
    if (player->get_sprite_id() == Model::TextureID::NO_TEXTURE) return;

    // Get the view from the camera
    coord_t viewport_width = camera.get_viewport_width();
    coord_t viewport_height = camera.get_viewport_height();

    SDL2pp::Point camera_view = camera.get_camera_view(player->get_position());
    int camera_view_x = camera_view.GetX();
    int camera_view_y = camera_view.GetY();

    // Calculate player's size given the viewport and keeping aspect ratio
    SDL2pp::Point player_display_size = scalator(window->GetSize(), true);

    // Skip rendering if the player is outside the viewport
    if (camera_view_x >= viewport_width + (player_display_size.GetX() / 2) ||
        camera_view_y >= viewport_height + (player_display_size.GetY() / 2) ||
        camera_view_x + (player_display_size.GetX() / 2) <= 0 ||
        camera_view_y + (player_display_size.GetY() / 2) <= 0) {
        return;
    }

    set_player_to_be_rendered(player, camera_view, player_display_size);
    set_weapon_to_be_rendered(player, camera_view, player_display_size);
    set_name_to_be_rendered(player, camera_view, player_display_size);
}

void View::PlayerRenderer::render_fov(angle_t angle) {
    auto viewport = game_state_manager->get_camera().get_viewport();
    int viewport_width = viewport.GetX();
    int viewport_height = viewport.GetY();

    // Id del fov_textureMore actions
    auto fov_texture = asset_manager->get_texture(Model::TextureID::FOV);

    // Squared texture
    int fov_texture_size = fov_texture->GetWidth();

    int slice_radius = std::sqrt(
        (640 * 640) + (480 * 480)
    ) / 2;
    int max_length_to_corners = std::sqrt(
        (viewport_width * viewport_width) + (viewport_height * viewport_height)
    ) / 2;

    renderer->Copy(
        *fov_texture,
        SDL2pp::Rect(
            (fov_texture_size - 2 * slice_radius) / 2,
            (fov_texture_size - 2 * slice_radius) / 2,
            2 * slice_radius,
            2 * slice_radius
        ),
        SDL2pp::Rect(
            (viewport_width - 2 * max_length_to_corners) / 2,
            (viewport_height - 2 * max_length_to_corners) / 2,
            2 * max_length_to_corners,
            2 * max_length_to_corners
        ),
        angle
    );
}

View::PlayerRenderer::PlayerRenderer(
    Weak<Controller::GameController> controller
): View::Renderer(controller),
   mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
   chunk("assets/sfx/weapons/fiveseven.wav"),
   controller(controller),
   background(controller),
   fov(controller) {
    auto controller_locked = controller.lock();

    SDL_Rect bounds;
    SDL_GetDisplayBounds(0, &bounds);
    scalator.set_max_bounds(SDL2pp::Point(bounds.w, bounds.h));
    scalator.set_min_bounds(SDL2pp::Point(640, 480));
    scalator.set_max_size(SDL2pp::Point(64, 64));
    scalator.set_min_size(SDL2pp::Point(32, 32));

    game_state_manager = controller_locked->get_game_state_manager();
    font = asset_manager->generate_font("liberationsans", 16);
    background.set_background_color(0, 255, 0, 100);
    background.set_draw_background(true);
}

void View::PlayerRenderer::render() {
    game_sprites.clear();
    background.clear_children();
    auto camera = game_state_manager->get_camera();
    angle_t fov_angle = 0;

    game_state_manager->call_function_on_players(
        [this, &camera, &fov_angle] (std::map<short_id_t, Shared<View::RenderedPlayer>>& map) {
            Shared<View::RenderedPlayer> reference_player = nullptr;
            short_id_t reference_player_id = game_state_manager->get_reference_player_id();

            for (auto& pair : map) {
                if (pair.first == reference_player_id) {
                    reference_player = pair.second;
                } else {
                    load_player(camera, pair.second);
                }
            }

            fov_angle = reference_player->get_angle();
            load_player(camera, reference_player);
        }
    );

    background.render();
    render_fov(fov_angle);

    game_state_manager->map_function_on_pending_weapon_usages(
        [this] (Shared<View::RenderedPlayer>&) {
            (void) mixer.PlayChannel(-1, chunk);
        }
    );
};

void View::PlayerRenderer::update_size() {
    background.set_max_size(renderer->GetViewport().GetSize());
    background.set_size(renderer->GetViewport().GetSize());
}
