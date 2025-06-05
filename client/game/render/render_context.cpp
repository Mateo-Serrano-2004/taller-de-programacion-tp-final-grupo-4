#include "render_context.h"

View::RenderContext::RenderContext(SDL2pp::Window& window, SDL2pp::Renderer& renderer,
                                         Model::AssetManager& asset_manager)
                                         : window(window),
                                           renderer(renderer),
                                           asset_manager(asset_manager) {}
