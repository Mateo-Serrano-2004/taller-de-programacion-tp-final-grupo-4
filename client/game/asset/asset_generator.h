#ifndef CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H
#define CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace SDL2pp {
class Renderer;
class Texture;
class Point;
class Color;
class Font;
};  // namespace SDL2pp

namespace DTO {
struct MapDTO;
};

namespace View {
class AssetGenerator {
protected:
    Shared<SDL2pp::Renderer> renderer;

    SDL_Rect get_bounds();

    void draw_disk(int size, int radius);
    void draw_triangle(int half_size, int angle);

    std::unordered_map<std::string, Shared<SDL2pp::Texture>> load_tiles(const DTO::MapDTO& map_dto);
    void insert_tiles(Shared<SDL2pp::Texture> texture, const DTO::MapDTO& map_dto,
                      std::unordered_map<std::string, Shared<SDL2pp::Texture>>& tiles);

public:
    explicit AssetGenerator(Shared<SDL2pp::Renderer> renderer);

    // Generate assets from scratch

    // FOV = Field of view
    Shared<SDL2pp::Texture> generate_fov();
    Shared<SDL2pp::Texture> generate_plain_texture(const SDL2pp::Point& size,
                                                   const SDL2pp::Color& color);
    Shared<SDL2pp::Texture> generate_plain_texture(const SDL2pp::Color& color);
    Shared<SDL2pp::Texture> generate_map(const DTO::MapDTO& map_dto);
    Shared<SDL2pp::Font> generate_font(const std::string& path, uint8_t size);

    ~AssetGenerator() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H
