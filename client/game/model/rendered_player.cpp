#include "rendered_player.h"

#include <utility>

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

View::RenderedPlayer::RenderedPlayer(Model::Player&& player)
: Model::Player(std::move(player)),
  sprite_id(Model::TextureID::NO_TEXTURE),
  sprite_piece(0),
  weapon_sprite_id(Model::TextureID::NO_TEXTURE) {
    sprite_piece = get_sprite_piece_from_weapon();
}

Model::TextureID View::RenderedPlayer::get_sprite_id() const { return sprite_id; }

short_id_t View::RenderedPlayer::get_sprite_piece() const { return sprite_piece; }

Model::TextureID View::RenderedPlayer::get_weapon_sprite_id() const { return weapon_sprite_id; }

void View::RenderedPlayer::set_sprite_id(Model::TextureID new_sprite_id) {
    sprite_id = new_sprite_id;
}

void View::RenderedPlayer::set_sprite_piece(short_id_t new_sprite_piece) {
    sprite_piece = new_sprite_piece;
}

void View::RenderedPlayer::set_weapon_sprite_id(Model::TextureID new_weapon_sprite_id) {
    weapon_sprite_id = new_weapon_sprite_id;
}
