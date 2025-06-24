#ifndef CLIENT_GAME_ENUM_ENUM_TRANSLATOR_H
#define CLIENT_GAME_ENUM_ENUM_TRANSLATOR_H

#include <map>

#include "asset/sound_id.h"
#include "asset/texture_id.h"
#include "common/definitions.h"
#include "common/role_id.h"
#include "common/weapon_id.h"

namespace Model {
class EnumTranslator {
private:
    static std::map<Model::RoleID, Model::TextureID> roles_to_textures;
    static std::map<Model::TextureID, Model::RoleID> textures_to_roles;
    static std::map<Model::WeaponID, Model::TextureID> weapons_to_textures;
    static std::map<Model::WeaponID, Model::TextureID> weapons_to_hud_textures;
    static std::map<Model::WeaponID, Model::TextureID> weapons_to_dropped;
    static std::map<Model::WeaponID, Model::SoundID> weapons_to_sounds;

    static void build_roles_to_textures();
    static void build_textures_to_roles();
    static void build_weapons_to_textures();
    static void build_weapons_to_hud_textures();
    static void build_weapons_to_dropped();
    static void build_weapons_to_sounds();

public:
    static void build();

    static Model::RoleID get_role_from_texture(Model::TextureID texture_id);
    static Model::TextureID get_texture_from_role(Model::RoleID role_id);
    static Model::TextureID get_texture_from_weapon(Model::WeaponID weapon_id);
    static Model::TextureID get_hud_texture_from_weapon(Model::WeaponID weapon_id);
    static Model::TextureID get_dropped_from_weapon(Model::WeaponID weapon_id);
    static Model::SoundID get_sound_from_weapon(Model::WeaponID weapon_id);
};
};  // namespace Model

#endif  // CLIENT_GAME_ENUM_ENUM_TRANSLATOR_H
