#include "rendered_player.h"

#include <utility>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "controller/game_controller.h"
#include "utils/enum_translator.h"

short_id_t View::RenderedPlayer::get_sprite_piece_from_weapon() {
    switch (current_weapon->get_weapon_id()) {
        case Model::WeaponID::KNIFE:
            return 0;
        case Model::WeaponID::GLOCK:
            return 3;
        default:
            return 4;
    }
}

SDL2pp::Point View::RenderedPlayer::get_sprite_top_left_corner() {
    uint16_t sprite_row = sprite_piece ? static_cast<uint16_t>(sprite_piece / 2) : 0;
    uint16_t sprite_column = static_cast<uint16_t>(sprite_piece % 2);

    uint16_t sprite_piece_x = sprite_column * 32;
    uint16_t sprite_piece_y = sprite_row * 32;

    return SDL2pp::Point(sprite_piece_x, sprite_piece_y);
}

void View::RenderedPlayer::render_weapon(const SDL2pp::Point& player_center) {
    Shared<SDL2pp::Texture> weapon_texture = asset_manager->get_texture(weapon_sprite_id);

    SDL2pp::Rect weapon_coords(player_center.GetX() - 16, player_center.GetY() - 32, 32, 32);
    SDL2pp::Point point_to_rotate(16, 32);

    renderer->Copy(*weapon_texture, SDL2pp::NullOpt, weapon_coords, angle, point_to_rotate);
}

void View::RenderedPlayer::render_name(const SDL2pp::Point& player_center) {
    Shared<SDL2pp::Texture> text =
            asset_manager->apply_font_to_text(asset_manager->generate_font("liberationsans", 16),
                                              name, SDL2pp::Color(255, 255, 255, 255));
    renderer->Copy(*text, SDL2pp::NullOpt,
                   SDL2pp::Rect(player_center.GetX() - (text->GetWidth()) / 2,
                                player_center.GetY() - 17 - text->GetHeight(), text->GetWidth(),
                                text->GetHeight()));
}

View::RenderedPlayer::RenderedPlayer(Weak<Controller::GameController> controller,
                                     Model::Player&& player):
        View::Rendered(controller),
        Fixed(),
        Model::Player(std::move(player)),
        asset_manager(controller.lock()->get_asset_manager()),
        sprite_id(Model::EnumTranslator::get_texture_from_role(role_id)),
        sprite_piece(get_sprite_piece_from_weapon()),
        weapon_sprite_id(
                Model::EnumTranslator::get_texture_from_weapon(current_weapon->get_weapon_id())) {}

void View::RenderedPlayer::render() {
    if (team == Model::TeamID::NONE || sprite_id == Model::TextureID::NO_TEXTURE)
        return;
    if (!health)
        return;
    Shared<SDL2pp::Texture> texture = asset_manager->get_texture(sprite_id);
    SDL2pp::Point sprite_top_left_corner = get_sprite_top_left_corner();

    coord_t viewport_width = camera.get_viewport_width();
    coord_t viewport_height = camera.get_viewport_height();

    SDL2pp::Point camera_view = camera.get_camera_view(position);
    int camera_view_x = camera_view.GetX();
    int camera_view_y = camera_view.GetY();

    if (camera_view_x >= viewport_width + 15 || camera_view_y >= viewport_height + 15 ||
        camera_view_x + 15 <= 0 || camera_view_y + 15 <= 0) {
        return;
    }

    SDL2pp::Rect sprite_rect(sprite_top_left_corner.GetX(), sprite_top_left_corner.GetY(), 32, 32);

    SDL2pp::Point top_left_corner(camera_view_x - 16, camera_view_y - 16);

    renderer->Copy(*texture, sprite_rect, top_left_corner, angle, SDL2pp::NullOpt);

    render_weapon(camera_view);
    render_name(camera_view);
}
