#ifndef CLIENT_GAME_TEXTURE_TEXTURE_STORAGE_H
#define CLIENT_GAME_TEXTURE_TEXTURE_STORAGE_H

#include <map>
#include <string>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "common/definitions.h"

namespace Model {

class TextureStorage {
private:
    Weak<SDL2pp::Renderer> renderer;
    std::map<size_t, SDL2pp::Texture> textures;

public:
    explicit TextureStorage(Weak<SDL2pp::Renderer> renderer);

    void load_texture(size_t id, const std::string& pathname);
    SDL2pp::Texture& get_texture(size_t id);

    ~TextureStorage() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_TEXTURE_TEXTURE_STORAGE_H
