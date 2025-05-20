#include "client/game/texture/sdl_texture.h"

#include <SDL2pp/SDL2pp.hh>

#include "../render/sdl_renderer.h"

View::SDLTexture::SDLTexture(
        SDLRenderer* sdl_renderer,
        const std::string& pathname
    ) : renderer(sdl_renderer),
        texture(*(sdl_renderer->get_renderer()), pathname) {}

void View::SDLTexture::render() {
    renderer->get_renderer()->Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::NullOpt
    );
}
