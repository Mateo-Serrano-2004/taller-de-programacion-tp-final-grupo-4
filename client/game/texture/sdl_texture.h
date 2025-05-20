#ifndef CLIENT_GAME_TEXTURE_SDL_TEXTURE_H
#define CLIENT_GAME_TEXTURE_SDL_TEXTURE_H

#include <SDL2pp/Texture.hh>

// #include "../render/sdl_renderer.h"

namespace View {

    class SDLRenderer;

    class SDLTexture {
    protected:
        SDLRenderer* renderer;
        SDL2pp::Texture texture;

    public:
        SDLTexture(
            SDLRenderer* sdl_renderer,
            const std::string& pathname
        );

        void render();

        ~SDLTexture() = default;
    };
};

#endif // CLIENT_GAME_TEXTURE_SDL_TEXTURE_H
