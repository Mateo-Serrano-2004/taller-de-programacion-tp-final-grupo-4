#ifndef CLIENT_GAME_ASSET_ASSET_LOADER_H
#define CLIENT_GAME_ASSET_ASSET_LOADER_H

#include <string>
#include <vector>

#include "common/DTO/config_dto.h"
#include "common/asset_addresser.h"
#include "common/definitions.h"

#include "asset_generator.h"
#include "texture_id.h"

namespace SDL2pp {
class Renderer;
};

namespace Controller {
class GameController;
};

namespace Model {
class AssetManager;

class AssetLoader {
private:
    AssetAddresser addresser;
    std::vector<std::string> player_sprites;
    std::vector<std::string> weapon_sprites;
    std::vector<std::string> dropped_weapon_sprites;
    std::vector<std::string> hud_textures;
    std::vector<std::string> sounds;
    Shared<AssetManager> manager;
    Shared<SDL2pp::Renderer> renderer;
    DTO::ConfigDTO config;
    View::AssetGenerator generator;

    void load_weapon_sprites();
    void load_dropped_weapon_sprites();
    void load_player_sprites();
    void load_from_surface(Model::TextureID id, const std::string& path);
    void load_hud_textures();
    void load_fov();
    void load_bomb_animation();
    void load_shot_animation();
    void load_animations();
    void load_sounds();
    void load_cursor();

public:
    AssetLoader(Shared<AssetManager> manager, Shared<SDL2pp::Renderer> renderer,
                const DTO::ConfigDTO& config);

    void load_all_textures();

    ~AssetLoader() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_ASSET_ASSET_LOADER_H
