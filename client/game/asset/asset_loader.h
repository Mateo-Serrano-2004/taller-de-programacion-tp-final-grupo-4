#ifndef CLIENT_GAME_ASSET_ASSET_LOADER_H
#define CLIENT_GAME_ASSET_ASSET_LOADER_H

#include <string>
#include <vector>

#include "common/asset_addresser.h"
#include "common/definitions.h"
#include "common/DTO/config_dto.h"

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
    std::vector<std::string> hud_textures;
    Shared<AssetManager> manager;
    Shared<SDL2pp::Renderer> renderer;
    DTO::ConfigDTO config;
    View::AssetGenerator generator;

    void load_weapon_sprites();
    void load_player_sprites();
    void load_hud_texture(Model::TextureID id, int index);
    void load_hud_textures();
    void load_fov();
    void load_animations();
    void load_white_background();

public:
    AssetLoader(
        Shared<AssetManager> manager,
        Shared<SDL2pp::Renderer> renderer,
        const DTO::ConfigDTO& config
    );

    void load_all_textures();

    ~AssetLoader() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_ASSET_ASSET_LOADER_H
