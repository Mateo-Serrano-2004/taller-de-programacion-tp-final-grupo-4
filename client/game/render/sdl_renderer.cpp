#include "sdl_renderer.h"

#include <list>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "../model/game_state.h"
#include "../texture/texture_storage.h"

View::SDLRenderer::SDLRenderer(
    App::SDLWindow* sdl_window,
    Model::GameState* game_state,
    Model::TextureStorage* texture_storage
) : window(sdl_window),
    game_state(game_state),
    texture_storage(texture_storage),
    renderer(sdl_window->get_window(), -1, SDL_RENDERER_ACCELERATED) {}

void View::SDLRenderer::render_player(const Model::Player& player) {
    uint16_t x = player.get_x();
    uint16_t y = player.get_y();

    if (x + 31 <= 0 || y + 31 <= 0 || x >= 640 || y >= 480) return;

    uint16_t skin_id = player.get_skin_id();
    uint8_t skin_piece = player.get_skin_piece();

    uint8_t skin_row = (uint8_t) ((skin_piece - 1) / 2);
    uint8_t skin_column = skin_piece % 2;

    uint skin_piece_x = skin_column * 32;
    uint skin_piece_y = skin_row * 32;

    renderer.Copy(
        texture_storage->get_texture(skin_id),
        SDL2pp::Rect(
            skin_piece_x, skin_piece_y,
            32, 32
        ),
        SDL2pp::Point(x, y)
    );
}

void View::SDLRenderer::render() {
    const auto& players = game_state->get_players();
    for (auto& player : players) {
        render_player(player);
    }
    renderer.Present();
}

SDL2pp::Renderer* View::SDLRenderer::get_renderer() {
    return &renderer;
}
