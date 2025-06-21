#include "number_texture_slicer.h"

#include <utility>
#include <vector>
#include <cmath>
#include <SDL2pp/Rect.hh>

#include "asset/asset_manager.h"
#include "asset/texture_id.h"

std::vector<int> View::NumberTextureSlicer::get_units(int number) {
    int number_of_digits = number ? (int) (log10(number) + 1) : 1;
    std::vector<int> digits(number_of_digits);
    for (int i = 0; i < number_of_digits; i++) {
        digits[number_of_digits - i - 1] = number % 10;
        number /= 10;
    }
    return digits;
}

std::vector<SDL2pp::Rect> View::NumberTextureSlicer::get_hud_number(int number) {
    std::vector<SDL2pp::Rect> numbers_slices;
    auto units = View::NumberTextureSlicer::get_units(number);
    for (auto& unit : units) {
        numbers_slices.push_back(SDL2pp::Rect(unit * 44, 0, 44, 66));
    }
    return numbers_slices;
}

SDL2pp::Rect View::NumberTextureSlicer::get_separator() {
    return SDL2pp::Rect(440, 0, 12, 66);
}
