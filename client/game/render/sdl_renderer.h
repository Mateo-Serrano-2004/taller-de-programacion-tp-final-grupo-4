#ifndef CLIENT_GAME_RENDER_SDL_RENDERER_H
#define CLIENT_GAME_RENDER_SDL_RENDERER_H

#include <utility>

#include <SDL2pp/Renderer.hh>

#include "window/sdl_window.h"

namespace Model {
class GameState;
class Player;
class TextureStorage;
};  // namespace Model

namespace View {
class SDLRenderer {
private:
    App::SDLWindow* window;
    Model::GameState* game_state;
    Model::TextureStorage* texture_storage;
    SDL2pp::Renderer renderer;

    std::pair<int16_t, int16_t> get_skin_piece(const Model::Player& player);
    void render_player(const Model::Player& player);

public:
    SDLRenderer(App::SDLWindow* sdl_window, Model::GameState* game_state,
                Model::TextureStorage* texture_storage);

    void render();
    SDL2pp::Renderer* get_renderer();

    ~SDLRenderer() = default;
};
}  // namespace View

#endif  // CLIENT_GAME_RENDER_SDL_RENDERER_H
