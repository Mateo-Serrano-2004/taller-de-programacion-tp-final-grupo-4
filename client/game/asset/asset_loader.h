#ifndef CLIENT_GAME_ASSET_ASSET_LOADER_H
#define CLIENT_GAME_ASSET_ASSET_LOADER_H

#include <string>
#include <vector>

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

namespace DTO {
struct ConfigDTO;
}

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
    View::AssetGenerator generator;

    void load_weapon_sprites();
    void load_player_sprites();
    void load_hud_texture(Model::TextureID id, int index);
    void load_hud_textures();
    void load_fov(const DTO::ConfigDTO& config);
    void load_animations();

public:
    AssetLoader(Shared<AssetManager> manager, Shared<SDL2pp::Renderer> renderer);

    void load_all_textures(const DTO::ConfigDTO& config);

    ~AssetLoader() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_ASSET_ASSET_LOADER_H
