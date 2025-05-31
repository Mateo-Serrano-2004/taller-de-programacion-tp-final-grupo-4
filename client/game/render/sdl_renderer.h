#ifndef CLIENT_GAME_RENDER_SDL_RENDERER_H
#define CLIENT_GAME_RENDER_SDL_RENDERER_H

#include <utility>

#include <SDL2pp/Renderer.hh>

#include "window/sdl_window.h"

namespace Controller {
class GameStateManager;
};

namespace Model {
class Player;
class TextureStorage;
};  // namespace Model

namespace View {
class SDLRenderer {
private:
    App::SDLWindow* window;
    Controller::GameStateManager* game_state_manager;
    Model::TextureStorage* texture_storage;
    SDL2pp::Renderer renderer;

    std::pair<uint16_t, uint16_t> get_skin_piece(const Model::Player& player);
    void render_player(const Model::Player& player);

public:
    SDLRenderer(App::SDLWindow* sdl_window, Controller::GameStateManager* game_state_manager,
                Model::TextureStorage* texture_storage);

    void render();
    SDL2pp::Renderer* get_renderer();

    ~SDLRenderer() = default;
};
}  // namespace View

#endif  // CLIENT_GAME_RENDER_SDL_RENDERER_H
