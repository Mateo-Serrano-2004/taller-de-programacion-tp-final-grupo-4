#ifndef CLIENT_GAME_CS2D_APP_H
#define CLIENT_GAME_CS2D_APP_H

#include "common/definitions.h"

#include "application.h"

namespace Net {
class ClientProtocol;
};

namespace App {
class CS2DApp: public Application {
protected:
    CS2DApp(const CS2DApp&) = delete;
    CS2DApp& operator=(const CS2DApp&) = delete;
    CS2DApp(CS2DApp&&) = delete;
    CS2DApp& operator=(CS2DApp&&) = delete;

    void load_weapon_sprites(Shared<Model::AssetManager> asset_manager);
    void load_player_sprites(Shared<Model::AssetManager> asset_manager);
    void load_generated_textures(Shared<Model::AssetManager> asset_manager, Shared<SDL2pp::Renderer> renderer);
    void load_fonts(Shared<Model::AssetManager> asset_manager);

public:
    CS2DApp(Net::ClientProtocol* protocol);

    ~CS2DApp() override = default;
};
};

#endif // CLIENT_GAME_CS2D_APP_H
