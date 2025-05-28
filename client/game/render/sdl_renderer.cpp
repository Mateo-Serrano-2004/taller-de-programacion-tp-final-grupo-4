#include "sdl_renderer.h"

#include <list>
#include <string>
#include <utility>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "model/game_state.h"
#include "texture/texture_storage.h"

View::SDLRenderer::SDLRenderer(
    App::SDLWindow* sdl_window,
    Model::GameState* game_state,
    Model::TextureStorage* texture_storage
) : window(sdl_window),
    game_state(game_state),
    texture_storage(texture_storage),
    renderer(sdl_window->get_window(), -1, SDL_RENDERER_ACCELERATED) {}

std::pair<int16_t, int16_t> View::SDLRenderer::get_skin_piece(const Model::Player& player) {
    uint8_t skin_piece = player.get_skin_piece();

    uint8_t skin_row = (uint8_t) ((skin_piece - 1) / 2);
    uint8_t skin_column = skin_piece % 2;

    uint16_t skin_piece_x = skin_column * 32;
    uint16_t skin_piece_y = skin_row * 32;

    std::pair<uint16_t, uint16_t> skin = std::make_pair(skin_piece_x, skin_piece_y);

    return skin;
}

void View::SDLRenderer::render_player(const Model::Player& player) {
    auto& reference_player = game_state->get_reference_player();
    auto skin_piece = get_skin_piece(player);

    uint16_t reference_id = reference_player.get_id();
    int32_t reference_x = reference_player.get_x();
    int32_t reference_y = reference_player.get_y();

    uint16_t id = player.get_id();
    uint16_t skin_id = player.get_skin_id();
    int32_t x = player.get_x();
    int32_t y = player.get_y();

    if (id == reference_id) {
        renderer.Copy(
            texture_storage->get_texture(skin_id),
            SDL2pp::Rect(
                skin_piece.first, skin_piece.second,
                32, 32
            ),
            SDL2pp::Point((window->get_width() / 2) - 15, (window->get_height() / 2) - 15),
            player.get_angle(),
            SDL2pp::NullOpt,
            0
        );
    } else {
        renderer.Copy(
            texture_storage->get_texture(skin_id),
            SDL2pp::Rect(
                skin_piece.first, skin_piece.second,
                32, 32
            ),
            SDL2pp::Point(x - reference_x, y - reference_y),
            player.get_angle(),
            SDL2pp::NullOpt,
            0
        );
    }
}

void View::SDLRenderer::render() {
    renderer.Clear();
    const auto& players = game_state->get_players();
    for (auto& player : players) {
        render_player(player.second);
    }
    renderer.Present();
}

SDL2pp::Renderer* View::SDLRenderer::get_renderer() {
    return &renderer;
}
