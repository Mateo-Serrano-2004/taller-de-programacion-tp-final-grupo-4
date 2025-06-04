#ifndef CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H
#define CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H

#include <SDL2/SDL.h>
#include <SDL2pp/Texture.hh>

#include "common/definitions.h"

namespace SDL2pp {
class Renderer;
};

namespace View {
class TextureGenerator {
protected:
    Shared<SDL2pp::Renderer> renderer;

    SDL_Rect get_bounds();

    void draw_disk(int size, int radius);
    void draw_triangle(int half_size, int angle);

public:
    TextureGenerator(Shared<SDL2pp::Renderer> renderer);

    // FOV = Field of view
    SDL2pp::Texture generate_fov();
    SDL2pp::Texture generate_background(const SDL2pp::Point& size, const SDL2pp::Color& color);
    SDL2pp::Texture generate_background(const SDL2pp::Color& color);

    ~TextureGenerator() = default;
};
};

#endif // CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H
