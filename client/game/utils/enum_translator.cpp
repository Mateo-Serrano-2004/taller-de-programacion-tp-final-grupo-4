#include "enum_translator.h"

std::map<Model::RoleID, Model::TextureID> Model::EnumTranslator::roles_to_textures;
std::map<Model::TextureID, Model::RoleID> Model::EnumTranslator::textures_to_roles;
std::map<Model::WeaponID, Model::TextureID> Model::EnumTranslator::weapons_to_textures;

void Model::EnumTranslator::build_roles_to_textures() {
    roles_to_textures = {{Model::RoleID::CT1, Model::TextureID::SPRITE_CT1},
                         {Model::RoleID::CT2, Model::TextureID::SPRITE_CT2},
                         {Model::RoleID::CT3, Model::TextureID::SPRITE_CT3},
                         {Model::RoleID::CT4, Model::TextureID::SPRITE_CT4},
                         {Model::RoleID::T1, Model::TextureID::SPRITE_T1},
                         {Model::RoleID::T2, Model::TextureID::SPRITE_T2},
                         {Model::RoleID::T3, Model::TextureID::SPRITE_T3},
                         {Model::RoleID::T4, Model::TextureID::SPRITE_T4},
                         {Model::RoleID::NO_ROLE, Model::TextureID::SPRITE_CT1}};
}

void Model::EnumTranslator::build_textures_to_roles() {
    textures_to_roles = {{Model::TextureID::SPRITE_CT1, Model::RoleID::CT1},
                         {Model::TextureID::SPRITE_CT2, Model::RoleID::CT2},
                         {Model::TextureID::SPRITE_CT3, Model::RoleID::CT3},
                         {Model::TextureID::SPRITE_CT4, Model::RoleID::CT4},
                         {Model::TextureID::SPRITE_T1, Model::RoleID::T1},
                         {Model::TextureID::SPRITE_T2, Model::RoleID::T2},
                         {Model::TextureID::SPRITE_T3, Model::RoleID::T3},
                         {Model::TextureID::SPRITE_T4, Model::RoleID::T4},
                         {Model::TextureID::NO_TEXTURE, Model::RoleID::NO_ROLE}};
}

void Model::EnumTranslator::build_weapons_to_textures() {
    weapons_to_textures = {{Model::WeaponID::GLOCK, Model::TextureID::SPRITE_GLOCK},
                           {Model::WeaponID::AK47, Model::TextureID::SPRITE_AK47},
                           {Model::WeaponID::AWP, Model::TextureID::SPRITE_AWP},
                           {Model::WeaponID::M3, Model::TextureID::SPRITE_M3},
                           {Model::WeaponID::KNIFE, Model::TextureID::SPRITE_KNIFE},
                           {Model::WeaponID::BOMB, Model::TextureID::SPRITE_BOMB},
                           {Model::WeaponID::EMPTY, Model::TextureID::NO_TEXTURE}};
}

void Model::EnumTranslator::build() {
    build_roles_to_textures();
    build_textures_to_roles();
    build_weapons_to_textures();
}

Model::RoleID Model::EnumTranslator::get_role_from_texture(Model::TextureID texture_id) {
    return textures_to_roles.at(texture_id);
}

Model::TextureID Model::EnumTranslator::get_texture_from_role(Model::RoleID role_id) {
    return roles_to_textures.at(role_id);
}

Model::TextureID Model::EnumTranslator::get_texture_from_weapon(Model::WeaponID weapon_id) {
    return weapons_to_textures.at(weapon_id);
}
