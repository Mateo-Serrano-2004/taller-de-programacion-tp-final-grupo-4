#include "asset_addresser.h"

#include <string>

Model::AssetAddresser::AssetAddresser()
#ifdef DEBUG_MODE
        :
        assets_main_path("assets/")
#else
        :
        assets_main_path("/var/cs2d/assets/")
#endif
{
}

std::string Model::AssetAddresser::get_weapon_sprite_path(const std::string& partial_path) {
    return assets_main_path + "gfx/weapons/" + partial_path;
}

std::string Model::AssetAddresser::get_player_sprite_path(const std::string& partial_path) {
    return assets_main_path + "gfx/players/" + partial_path;
}

std::string Model::AssetAddresser::get_hud_resource(const std::string& partial_path) {
    return assets_main_path + "gfx/hud/" + partial_path;
}

std::string Model::AssetAddresser::get_font_path(const std::string& font_name) {
    return assets_main_path + "gfx/fonts/" + font_name + ".ttf";
}

std::string Model::AssetAddresser::get_tile_path(const std::string& partial_path) {
    return assets_main_path + "gfx/tiles/" + partial_path;
}

std::string Model::AssetAddresser::get_animation_path(const std::string& partial_path) {
    return assets_main_path + "gfx/animations/" + partial_path;
}

std::string Model::AssetAddresser::get_sound_path(const std::string& partial_path) {
    return assets_main_path + "sfx/" + partial_path;
}

std::string Model::AssetAddresser::get_cursor_path(const std::string& partial_path) {
    return assets_main_path + "gfx/cursors/" + partial_path;
}
