#include "render_context.h"

View::RenderContext::RenderContext(SDL2pp::Window& window, SDL2pp::Renderer& renderer,
                                         Model::TextureStorage& texture_storage)
                                         : window(window),
                                           renderer(renderer),
                                           texture_storage(texture_storage) {}
