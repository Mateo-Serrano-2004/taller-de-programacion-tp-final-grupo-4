#ifndef CLIENT_GAME_ASSET_ASSET_MANAGER_H
#define CLIENT_GAME_ASSET_ASSET_MANAGER_H

#include <map>
#include <string>

#include "common/definitions.h"
#include "common/texture_id.h"

#include "background_id.h"
#include "font_id.h"

namespace SDL2pp {
class Renderer;
class Texture;
class Font;
class Color;
};

namespace Model {
class AssetManager {
private:
    Shared<SDL2pp::Renderer> renderer;
    std::map<TextureID, Shared<SDL2pp::Texture>> textures;
    std::map<BackgroundID, Shared<SDL2pp::Texture>> backgrounds;
    std::map<FontID, Shared<SDL2pp::Font>> fonts;

public:
    AssetManager(Shared<SDL2pp::Renderer> renderer);

    void load_texture(TextureID id, const std::string& path);
    void load_texture(TextureID id, Shared<SDL2pp::Texture> texture);

    void load_background(BackgroundID id, Shared<SDL2pp::Texture> background);

    void load_font(FontID id, const std::string& path, int size);
    void load_font(FontID id, Shared<SDL2pp::Font> font);

    Shared<SDL2pp::Texture> get_texture(TextureID id);
    Shared<SDL2pp::Texture> get_background(BackgroundID id);
    Shared<SDL2pp::Font> get_font(FontID id);

    Shared<SDL2pp::Texture> apply_font_to_text(
        FontID id,
        const std::string& text,
        const SDL2pp::Color& color
    );

    ~AssetManager() = default;
};
};

#endif // CLIENT_GAME_ASSET_ASSET_MANAGER_H
