#include "texture_storage.h"

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Renderer.hh>

#include "assets.h"

Model::TextureStorage::TextureStorage(Weak<SDL2pp::Renderer> renderer):
        renderer(renderer) {}

void Model::TextureStorage::load_texture(size_t id, const std::string& pathname) {
    textures.insert({id, SDL2pp::Texture(*(renderer.lock()), get_texture_path(pathname))});
}

SDL2pp::Texture& Model::TextureStorage::get_texture(size_t id) { return textures.at(id); }
