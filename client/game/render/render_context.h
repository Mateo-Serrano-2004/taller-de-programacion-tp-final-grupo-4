#ifndef CLIENT_GAME_CONTEXT_RENDER_CONTEXT_H
#define CLIENT_GAME_CONTEXT_RENDER_CONTEXT_H

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "texture/texture_storage.h"

namespace View {
struct RenderContext {
public:
    SDL2pp::Window& window;
    SDL2pp::Renderer& renderer;
    Model::TextureStorage& texture_storage;

    RenderContext(
        SDL2pp::Window& window,
        SDL2pp::Renderer& renderer,
        Model::TextureStorage& texture_storage);

    RenderContext(const RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete;
    RenderContext(RenderContext&&) = default;
    RenderContext& operator=(RenderContext&&) = default;

    virtual ~RenderContext() = default;
};
};

#endif // CLIENT_GAME_CONTEXT_RENDER_CONTEXT_H
