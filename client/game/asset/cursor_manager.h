#ifndef CLIENT_GAME_ASSET_CURSOR_MANAGER_H
#define CLIENT_GAME_ASSET_CURSOR_MANAGER_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "asset/cursor_id.h"
#include "common/definitions.h"

namespace SDL2pp {
class Surface;
class Renderer;
class Rect;
class Point;
};  // namespace SDL2pp

namespace Model {
class CursorManager {
private:
    SDL_Cursor* cursor;
    Uint32 rmask;
    Uint32 gmask;
    Uint32 bmask;
    Uint32 amask;
    std::unordered_map<CursorID, Shared<SDL2pp::Surface>> cursors;
    Shared<SDL2pp::Renderer> renderer;

public:
    explicit CursorManager(Shared<SDL2pp::Renderer> renderer);

    void load_cursor_texture(Model::CursorID id, const std::string& path,
                             const SDL2pp::Rect& srect);
    void apply_cursor(CursorID id, const SDL2pp::Point& hotspot);

    ~CursorManager();
};
};  // namespace Model

#endif  // CLIENT_GAME_ASSET_CURSOR_MANAGER_H
