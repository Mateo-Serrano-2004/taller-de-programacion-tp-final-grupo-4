#include "sdl_window.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

App::SDLWindow::SDLWindow()
: sdl(SDL_INIT_VIDEO),
window(
    "Demo",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    640, 480,
    SDL_WINDOW_RESIZABLE
) {}

SDL2pp::Window& App::SDLWindow::get_window() {
    return window;
}
