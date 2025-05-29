#include "sdl_window.h"

#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

App::SDLWindow::SDLWindow():
        sdl(SDL_INIT_VIDEO),
        window("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
               SDL_WINDOW_RESIZABLE) {}

SDL2pp::Window& App::SDLWindow::get_window() { return window; }

uint16_t App::SDLWindow::get_width() const { return (uint16_t)window.GetWidth(); }

uint16_t App::SDLWindow::get_height() const { return (uint16_t)window.GetHeight(); }
