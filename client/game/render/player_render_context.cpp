#include "player_render_context.h"

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

View::PlayerRenderContext::PlayerRenderContext(SDL2pp::Window& window, SDL2pp::Renderer& renderer,
                                               Model::TextureStorage& texture_storage,
                                               View::Camera& camera):
                                               View::RenderContext(window,
                                                                   renderer,
                                                                   texture_storage),
                                               camera(camera) {}
