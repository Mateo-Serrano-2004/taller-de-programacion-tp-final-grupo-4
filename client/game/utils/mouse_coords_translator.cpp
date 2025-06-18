#include "mouse_coords_translator.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>

SDL2pp::Point MouseCoordsTranslator::get_logical_coords(Shared<SDL2pp::Renderer> renderer) {
    int absolute_x, absolute_y;
    float logical_x, logical_y;
    (void)SDL_GetMouseState(&absolute_x, &absolute_y);

    SDL_RenderWindowToLogical(renderer->Get(), absolute_x, absolute_y, &logical_x, &logical_y);
    return SDL2pp::Point((int)(logical_x), (int)(logical_y));
}
