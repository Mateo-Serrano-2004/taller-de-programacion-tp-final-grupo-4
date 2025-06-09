#ifndef CLIENT_GAME_ASSET_ASSET_MANAGER_H
#define CLIENT_GAME_ASSET_ASSET_MANAGER_H

#include <map>
#include <tuple>
#include <string>

#include "common/definitions.h"

#include "asset_generator.h"
#include "asset/texture_id.h"

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
    View::AssetGenerator asset_generator;
    std::map<TextureID, Shared<SDL2pp::Texture>> textures;
    std::map<color_tuple, Shared<SDL2pp::Texture>> backgrounds;
    std::map<FontID, Shared<SDL2pp::Font>> fonts;

public:
    AssetManager(Shared<SDL2pp::Renderer> renderer);

    void load_texture(TextureID id, const std::string& path);
    void load_texture(TextureID id, Shared<SDL2pp::Texture> texture);

    Shared<SDL2pp::Texture> generate_background(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    Shared<SDL2pp::Texture> generate_background(const SDL2pp::Color& color);

    void load_font(FontID id, const std::string& path, int size);
    void load_font(FontID id, Shared<SDL2pp::Font> font);

    Shared<SDL2pp::Texture> get_texture(TextureID id);
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
