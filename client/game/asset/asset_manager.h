#ifndef CLIENT_GAME_ASSET_ASSET_MANAGER_H
#define CLIENT_GAME_ASSET_ASSET_MANAGER_H

#include <map>
#include <tuple>
#include <string>

#include "common/definitions.h"
#include "common/asset_addresser.h"

#include "asset_generator.h"
#include "texture_id.h"
#include "animation_id.h"
#include "font_id.h"

namespace SDL2pp {
class Renderer;
class Texture;
class Font;
class Color;
};

namespace DTO {
struct MapDTO;
};

namespace Model {
class AssetManager {
private:
    AssetAddresser asset_addresser;
    Shared<SDL2pp::Renderer> renderer;
    View::AssetGenerator asset_generator;
    std::map<TextureID, Shared<SDL2pp::Texture>> textures;
    std::map<AnimationID, Shared<SDL2pp::Texture>> animations;
    std::map<color_tuple, Shared<SDL2pp::Texture>> backgrounds;
    std::map<font_tuple, Shared<SDL2pp::Font>> fonts;
    Shared<SDL2pp::Texture> current_map;

public:
    AssetManager(Shared<SDL2pp::Renderer> renderer);

    void load_texture(TextureID id, const std::string& path);
    void load_texture(TextureID id, Shared<SDL2pp::Texture> texture);
    void load_animation(AnimationID id, Shared<SDL2pp::Texture> animation);

    Shared<SDL2pp::Texture> generate_background(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    Shared<SDL2pp::Texture> generate_background(const SDL2pp::Color& color);

    Shared<SDL2pp::Font> generate_font(const std::string& name, uint8_t size);

    Shared<SDL2pp::Texture> generate_map(const DTO::MapDTO& map_dto);

    Shared<SDL2pp::Texture> get_texture(TextureID id);
    Shared<SDL2pp::Texture> get_animation(AnimationID id);

    Shared<SDL2pp::Texture> apply_font_to_text(
        Shared<SDL2pp::Font> font,
        const std::string& text,
        const SDL2pp::Color& color
    );

    ~AssetManager() = default;
};
};

#endif // CLIENT_GAME_ASSET_ASSET_MANAGER_H
