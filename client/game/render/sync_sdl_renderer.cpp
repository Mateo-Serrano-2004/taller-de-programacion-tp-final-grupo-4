#include "client/game/render/sync_sdl_renderer.h"

#include <iostream>

void View::SyncSDLRenderer::render() {
    await_for_message();
    if (valid_message) {
        texture_manager.render_textures();
        renderer.Present();
    }
}
