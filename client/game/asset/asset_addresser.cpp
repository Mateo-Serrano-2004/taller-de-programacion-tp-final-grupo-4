#include "asset_addresser.h"

#include <string>

Model::AssetAddresser::AssetAddresser() {
    #ifdef DEBUG_MODE
    assets_main_path = "assets/";
    #else
    assets_main_path = "/var/cs2d/assets/";
    #endif
}

std::string Model::AssetAddresser::get_sprite_path(const std::string& partial_path) {
    return assets_main_path + "gfx/player/" + partial_path;
}

std::string Model::AssetAddresser::get_font_path(const std::string& partial_path) {
    return assets_main_path + "gfx/fonts/" + partial_path;
}
