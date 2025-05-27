#include "texture_storage.h"

#include "render/sdl_renderer.h"
#include "assets.h"

Model::TextureStorage::TextureStorage(View::SDLRenderer* sdl_renderer)
: sdl_renderer(sdl_renderer->get_renderer()) {}

void Model::TextureStorage::load_texture(
    size_t id,
    const std::string& pathname
) {
    textures.insert({id, SDL2pp::Texture(*sdl_renderer, get_texture_path(pathname))});
}

SDL2pp::Texture& Model::TextureStorage::get_texture(size_t id) {
    return textures.at(id);
}
