#ifndef CLIENT_GAME_NUMBER_TEXTURE_GENERATOR_H
#define CLIENT_GAME_NUMBER_TEXTURE_GENERATOR_H

#include <utility>
#include <vector>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

namespace SDL2pp {
class Texture;
};

namespace Model {
class AssetManager;
};

namespace View {
class NumberTextureGenerator {
private:
    inline static Shared<Model::AssetManager> manager = nullptr; 
    inline static Shared<SDL2pp::Texture> hud_numbers = nullptr;

    static std::vector<int> get_units(int number);

public:
    static void build(Shared<Model::AssetManager> manager);
    static std::pair<std::vector<SDL2pp::Rect>, Shared<SDL2pp::Texture>> get_hud_number(int number);
    static std::pair<SDL2pp::Rect, Shared<SDL2pp::Texture>> get_separator();
};
};

#endif // CLIENT_GAME_NUMBER_TEXTURE_GENERATOR_H
