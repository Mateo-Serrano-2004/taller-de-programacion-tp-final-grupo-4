#ifndef COMMON_ASSET_ADDRESSER_H
#define COMMON_ASSET_ADDRESSER_H

#include <string>

namespace Model {
class AssetAddresser {
private:
    std::string assets_main_path;

public:
    AssetAddresser();

    std::string get_weapon_sprite_path(const std::string& partial_path);
    std::string get_player_sprite_path(const std::string& partial_path);
    std::string get_hud_resource(const std::string& partial_path);
    std::string get_font_path(const std::string& font_name);
    std::string get_tile_path(const std::string& partial_path);
    std::string get_animation_path(const std::string& partial_path);
    std::string get_sound_path(const std::string& partial_path);
    std::string get_cursor_path(const std::string& partial_path);
};
};  // namespace Model

#endif  // COMMON_ASSET_ADDRESSER_H
