#include "number_texture_generator.h"

#include <utility>
#include <vector>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Rect.hh>

#include "asset/asset_manager.h"
#include "asset/texture_id.h"

std::vector<int> View::NumberTextureGenerator::get_units(int number) {
    int number_of_digits = number ? (int) (log10(number) + 1) : 1;
    std::vector<int> digits(number_of_digits);
    for (int i = 0; i < number_of_digits; i++) {
        digits[number_of_digits - i - 1] = number % 10;
        number /= 10;
    }
    return digits;
}

void View::NumberTextureGenerator::build(Shared<Model::AssetManager> manager) {
    View::NumberTextureGenerator::manager = manager;
    View::NumberTextureGenerator::hud_numbers = manager->get_texture(Model::TextureID::HUD_NUMS);
}

std::pair<std::vector<SDL2pp::Rect>, Shared<SDL2pp::Texture>> View::NumberTextureGenerator::get_hud_number(int number) {
    std::vector<SDL2pp::Rect> numbers_slices;
    auto units = View::NumberTextureGenerator::get_units(number);
    for (auto& unit : units) {
        numbers_slices.push_back(SDL2pp::Rect(unit * 44, 0, 44, 66));
    }
    return std::make_pair(
        numbers_slices,
        View::NumberTextureGenerator::hud_numbers
    );
}

std::pair<SDL2pp::Rect, Shared<SDL2pp::Texture>> View::NumberTextureGenerator::get_separator() {
    return std::make_pair(
        SDL2pp::Rect(440, 0, 12, 66),
        View::NumberTextureGenerator::hud_numbers
    );
}
