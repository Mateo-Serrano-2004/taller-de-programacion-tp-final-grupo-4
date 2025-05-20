#ifndef CLIENT_GAME_SDL_WINDOW_H
#define CLIENT_GAME_SDL_WINDOW_H

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>

#include "window.h"

namespace App {
    class SDLWindow : public Window {
    private:
        SDL2pp::SDL sdl;
        SDL2pp::Window window;

    public:
        SDLWindow();

        SDL2pp::Window& get_window();

        ~SDLWindow() override = default;
    };
};

#endif // CLIENT_GAME_SDL_WINDOW_H
