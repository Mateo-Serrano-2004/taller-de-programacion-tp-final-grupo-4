#ifndef CLIENT_GAME_TEXTURE_SDL_TEXTURE_MANAGER_H
#define CLIENT_GAME_TEXTURE_SDL_TEXTURE_MANAGER_H

#include <list>

// #include "../render/sdl_renderer.h"
#include "sdl_texture.h"

namespace View {

    class SDLRenderer;

    class SDLTextureManager {
    protected:
        SDLRenderer* renderer;
        std::list<SDLTexture> textures;

    public:
        SDLTextureManager(
            SDLRenderer* sdl_renderer,
            const std::list<std::string>& pathnames
        );

        void render_textures();

        ~SDLTextureManager() = default;
    };
};

#endif // CLIENT_GAME_TEXTURE_SDL_TEXTURE_MANAGER_H
