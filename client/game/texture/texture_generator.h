#ifndef CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H
#define CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H

#include <SDL2pp/Texture.hh>

#include "common/definitions.h"

namespace SDL2pp {
class Renderer;
};

namespace View {
class TextureGenerator {
protected:
    Shared<SDL2pp::Renderer> renderer;

    void draw_disk(int size, int radius);
    void draw_triangle(int half_size, int angle);

public:
    TextureGenerator(Shared<SDL2pp::Renderer> renderer);

    SDL2pp::Texture draw_field_of_view();

    ~TextureGenerator() = default;
};
};

#endif // CLIENT_GAME_TEXTURE_TEXTURE_GENERATOR_H
