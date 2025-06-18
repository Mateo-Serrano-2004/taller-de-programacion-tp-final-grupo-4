#ifndef CLIENT_GAME_UTILS_MOUSE_COORDS_TRANSLATOR_H
#define CLIENT_GAME_UTILS_MOUSE_COORDS_TRANSLATOR_H

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>

#include "common/definitions.h"

class MouseCoordsTranslator {
public:
    static SDL2pp::Point get_logical_coords(Shared<SDL2pp::Renderer> renderer);
};

#endif  // CLIENT_GAME_UTILS_MOUSE_COORDS_TRANSLATOR_H
