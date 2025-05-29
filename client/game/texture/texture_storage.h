#ifndef CLIENT_GAME_TEXTURE_TEXTURE_STORAGE_H
#define CLIENT_GAME_TEXTURE_TEXTURE_STORAGE_H

#include <list>
#include <map>
#include <string>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

namespace View {
class SDLRenderer;
};

namespace Model {

class TextureStorage {
private:
    SDL2pp::Renderer* sdl_renderer;
    std::map<size_t, SDL2pp::Texture> textures;

public:
    explicit TextureStorage(View::SDLRenderer* sdl_renderer);

    void load_texture(size_t id, const std::string& pathname);
    SDL2pp::Texture& get_texture(size_t id);

    ~TextureStorage() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_TEXTURE_TEXTURE_STORAGE_H
