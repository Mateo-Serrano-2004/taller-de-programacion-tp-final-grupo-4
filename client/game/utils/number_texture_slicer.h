#ifndef CLIENT_GAME_NUMBER_TEXTURE_SLICER_H
#define CLIENT_GAME_NUMBER_TEXTURE_SLICER_H

#include <utility>
#include <vector>

#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

namespace View {
class NumberTextureSlicer {
private:
    static std::vector<int> get_units(int number);

public:
    static std::vector<SDL2pp::Rect> get_hud_number(int number);
    static SDL2pp::Rect get_symbol(int symbol_number);
    static SDL2pp::Rect get_separator();
    static SDL2pp::Rect get_colon();
};
};  // namespace View

#endif  // CLIENT_GAME_NUMBER_TEXTURE_SLICER_H
