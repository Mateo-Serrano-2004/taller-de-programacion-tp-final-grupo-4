#include "enum_translator.h"

Model::EnumTranslator::EnumTranslator()
: roles_to_textures{
    {Model::RoleID::CT1, Model::TextureID::SPRITE_CT1},
    {Model::RoleID::CT2, Model::TextureID::SPRITE_CT2},
    {Model::RoleID::CT3, Model::TextureID::SPRITE_CT3},
    {Model::RoleID::CT4, Model::TextureID::SPRITE_CT4},
    {Model::RoleID::T1, Model::TextureID::SPRITE_T1},
    {Model::RoleID::T2, Model::TextureID::SPRITE_T2},
    {Model::RoleID::T3, Model::TextureID::SPRITE_T3},
    {Model::RoleID::T4, Model::TextureID::SPRITE_T4},
    {Model::RoleID::NO_ROLE, Model::TextureID::NO_TEXTURE}
  }, textures_to_roles{
    {Model::TextureID::SPRITE_CT1, Model::RoleID::CT1},
    {Model::TextureID::SPRITE_CT2, Model::RoleID::CT2},
    {Model::TextureID::SPRITE_CT3, Model::RoleID::CT3},
    {Model::TextureID::SPRITE_CT4, Model::RoleID::CT4},
    {Model::TextureID::SPRITE_T1, Model::RoleID::T1},
    {Model::TextureID::SPRITE_T2, Model::RoleID::T2},
    {Model::TextureID::SPRITE_T3, Model::RoleID::T3},
    {Model::TextureID::SPRITE_T4, Model::RoleID::T4},
    {Model::TextureID::NO_TEXTURE, Model::RoleID::NO_ROLE}
  }, weapons_to_textures{
    {Model::WeaponID::GLOCK, Model::TextureID::SPRITE_GLOCK},
    {Model::WeaponID::AK47, Model::TextureID::SPRITE_AK47},
    {Model::WeaponID::AWP, Model::TextureID::SPRITE_AWP},
    {Model::WeaponID::M3, Model::TextureID::SPRITE_M3},
    {Model::WeaponID::KNIFE, Model::TextureID::SPRITE_KNIFE},
    {Model::WeaponID::BOMB, Model::TextureID::SPRITE_BOMB},
    {Model::WeaponID::EMPTY, Model::TextureID::NO_TEXTURE}
  } {}

Model::RoleID Model::EnumTranslator::get_role_from_texture(Model::TextureID texture_id) {
    return textures_to_roles.at(texture_id);
}

Model::TextureID Model::EnumTranslator::get_texture_from_role(Model::RoleID role_id) {
    return roles_to_textures.at(role_id);
}

Model::TextureID Model::EnumTranslator::get_texture_from_weapon(Model::WeaponID weapon_id) {
    return weapons_to_textures.at(weapon_id);
}
