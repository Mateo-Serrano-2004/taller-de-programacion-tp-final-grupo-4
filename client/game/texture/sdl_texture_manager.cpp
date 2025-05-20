#include "sdl_texture_manager.h"

#include <list>
#include <string>

#include "../render/sdl_renderer.h"

View::SDLTextureManager::SDLTextureManager(
    SDLRenderer* sdl_renderer,
    const std::list<std::string>& pathnames
) : renderer(sdl_renderer) {
    for (const auto& pathname : pathnames) textures.emplace_back(renderer, pathname);
}

void View::SDLTextureManager::render_textures() {
    for (auto& texture : textures) texture.render();
}
