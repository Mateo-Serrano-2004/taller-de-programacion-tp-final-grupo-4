#include "cursor_manager.h"

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Surface.hh>

Model::CursorManager::CursorManager(Shared<SDL2pp::Renderer> renderer):
        cursor(nullptr),
        rmask(0x00ff0000),
        gmask(0x0000ff00),
        bmask(0x000000ff),
        amask(0xff000000),
        renderer(renderer) {}

void Model::CursorManager::load_cursor_texture(Model::CursorID id, const std::string& path,
                                               const SDL2pp::Rect& srect) {
    SDL2pp::Surface source(path);
    auto blit = make_shared<SDL2pp::Surface>(0, 20, 20, 32, rmask, gmask, bmask, amask);
    source.SetColorKey(true, SDL_MapRGB(source.Get()->format, 255, 0, 255));
    source.BlitScaled(srect, *blit, SDL2pp::Rect(0, 0, 20, 20));
    cursors.insert({id, blit});
}

void Model::CursorManager::apply_cursor(CursorID id, const SDL2pp::Point& hotspot) {
    if (cursor) {
        SDL_FreeCursor(cursor);
    }

    cursor = SDL_CreateColorCursor(cursors.at(id)->Get(), hotspot.GetX(), hotspot.GetY());
    SDL_SetCursor(cursor);
}

Model::CursorManager::~CursorManager() {
    if (cursor) {
        SDL_FreeCursor(cursor);
    }
}
