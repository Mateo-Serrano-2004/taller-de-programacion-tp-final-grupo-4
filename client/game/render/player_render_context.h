#ifndef CLIENT_GAME_CONTEXT_PLAYER_RENDER_CONTEXT_H
#define CLIENT_GAME_CONTEXT_PLAYER_RENDER_CONTEXT_H

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "render_context.h"
#include "camera.h"

namespace View {
struct PlayerRenderContext: public RenderContext {
public:
    Camera& camera;

    PlayerRenderContext(
        SDL2pp::Window& window,
        SDL2pp::Renderer& renderer,
        Model::AssetManager& asset_manager,
        Camera& camera);

    PlayerRenderContext(const PlayerRenderContext&) = delete;
    PlayerRenderContext& operator=(const PlayerRenderContext&) = delete;
    PlayerRenderContext(PlayerRenderContext&&) = default;
    PlayerRenderContext& operator=(PlayerRenderContext&&) = default;

    ~PlayerRenderContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_PLAYER_RENDER_CONTEXT_H
