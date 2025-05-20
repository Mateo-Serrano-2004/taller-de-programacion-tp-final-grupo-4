#ifndef CLIENT_GAME_RENDER_SDL_RENDERER_H
#define CLIENT_GAME_RENDER_SDL_RENDERER_H

#include <list>
#include <string>

#include <SDL2pp/Renderer.hh>

#include "../window/sdl_window.h"
#include "../texture/sdl_texture_manager.h"

namespace View {

    class SDLTextureManager;

    class SDLRenderer  {
    protected:
        App::SDLWindow* window;
        SDL2pp::Renderer renderer;
        SDLTextureManager texture_manager;

    public:
        SDLRenderer(
            App::SDLWindow* sdl_window,
            const std::list<std::string>& pathnames
        );

        virtual void render();
        SDL2pp::Renderer* get_renderer();

        virtual ~SDLRenderer() = default;
    };
}

#endif // CLIENT_GAME_RENDER_SDL_RENDERER_H
