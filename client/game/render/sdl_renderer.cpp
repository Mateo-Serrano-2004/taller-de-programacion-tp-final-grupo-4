#include "sdl_renderer.h"

#include <list>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

View::SDLRenderer::SDLRenderer(
    App::SDLWindow* sdl_window,
    const std::list<std::string>& pathnames
) : window(sdl_window),
    renderer(sdl_window->get_window(), -1, SDL_RENDERER_ACCELERATED),
    texture_manager(this, pathnames) {}

void View::SDLRenderer::render() {
    texture_manager.render_textures();
    renderer.Present();
}

SDL2pp::Renderer* View::SDLRenderer::get_renderer() {
    return &renderer;
}
