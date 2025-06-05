#ifndef CLIENT_GAME_CONTEXT_RENDER_CONTEXT_H
#define CLIENT_GAME_CONTEXT_RENDER_CONTEXT_H

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "asset/asset_manager.h"

namespace View {
struct RenderContext {
public:
    SDL2pp::Window& window;
    SDL2pp::Renderer& renderer;
    Model::AssetManager& asset_manager;

    RenderContext(
        SDL2pp::Window& window,
        SDL2pp::Renderer& renderer,
        Model::AssetManager& asset_manager);

    RenderContext(const RenderContext&) = delete;
    RenderContext& operator=(const RenderContext&) = delete;
    RenderContext(RenderContext&&) = default;
    RenderContext& operator=(RenderContext&&) = default;

    virtual ~RenderContext() = default;
};
};

#endif // CLIENT_GAME_CONTEXT_RENDER_CONTEXT_H
