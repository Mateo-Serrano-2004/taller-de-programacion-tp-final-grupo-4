#include "player_dto_parser.h"

#include "common/model/vector_2d.h"
#include "common/model/weapon.h"
#include "common/DTO/player_dto.h"

Model::TextureID DTO::PlayerDTOParser::get_texture_id(WeaponID weapon_id) {
    switch (weapon_id) {
        case WeaponID::KNIFE:
            return Model::TextureID::SPRITE_KNIFE;
        case WeaponID::GLOCK:
            return Model::TextureID::SPRITE_GLOCK;
        case WeaponID::AWP:
            return Model::TextureID::SPRITE_AWP;
        case WeaponID::M3:
            return Model::TextureID::SPRITE_M3;
        case WeaponID::AK47:
            return Model::TextureID::SPRITE_AK47;
        default:
            return Model::TextureID::SPRITE_BOMB;
    }
}

Model::Player DTO::PlayerDTOParser::parse(DTO::PlayerDTO&& player_dto) {
    return Model::Player(player_dto.player_id, player_dto.skin_id, player_dto.skin_piece,
                         player_dto.angle, player_dto.name,
                         Physics::Vector2D(player_dto.position_x, player_dto.position_y),
                         Model::Weapon(
                            (uint8_t) (get_texture_id((WeaponID) (player_dto.weapon_dto.weapon_id))),
                            player_dto.weapon_dto.loaded_ammo,
                            player_dto.weapon_dto.total_ammo
                        ));
}
