#ifndef CLIENT_GAME_ASSET_ASSET_ADDRESSER_H
#define CLIENT_GAME_ASSET_ASSET_ADDRESSER_H

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
    std::string get_font_path(const std::string& partial_path);
};
};

#endif // CLIENT_GAME_ASSET_ASSET_ADDRESSER_H
