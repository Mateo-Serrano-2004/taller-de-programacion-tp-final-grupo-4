#include "sdl_renderer.h"

#include <list>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/definitions.h"
#include "common/model/player.h"
#include "handler/game_state_manager.h"
#include "texture/texture_storage.h"

View::SDLRenderer::SDLRenderer(App::SDLWindow* sdl_window, Controller::GameStateManager* game_state_manager,
                               Model::TextureStorage* texture_storage):
        window(sdl_window),
        game_state_manager(game_state_manager),
        texture_storage(texture_storage),
        renderer(sdl_window->get_window(), -1, SDL_RENDERER_ACCELERATED) {}

std::pair<uint16_t, uint16_t> View::SDLRenderer::get_skin_piece(const Model::Player& player) {
    short_id_t skin_piece = player.get_skin_piece();

    uint16_t skin_row = skin_piece ? (uint16_t)((skin_piece - 1) / 2) : 0;
    uint16_t skin_column = (uint16_t)(skin_piece % 2);

    uint16_t skin_piece_x = skin_column * 32;
    uint16_t skin_piece_y = skin_row * 32;

    std::pair<uint16_t, uint16_t> skin = std::make_pair(skin_piece_x, skin_piece_y);

    return skin;
}

void View::SDLRenderer::render_player(const Model::Player& player) {
    Model::Player& reference_player = game_state_manager->get_reference_player();
    auto skin_piece = get_skin_piece(player);

    short_id_t reference_id = reference_player.get_id();
    Physics::Vector2D reference_position = reference_player.get_position();
    coord_t reference_x = reference_position.get_x();
    coord_t reference_y = reference_position.get_y();

    short_id_t id = player.get_id();
    short_id_t skin_id = player.get_skin_id();
    Physics::Vector2D position = player.get_position();
    coord_t x = position.get_x();
    coord_t y = position.get_y();

    if (id == reference_id) {
        renderer.Copy(
                texture_storage->get_texture(skin_id),
                SDL2pp::Rect(skin_piece.first, skin_piece.second, 32, 32),
                SDL2pp::Point((window->get_width() / 2) - 15, (window->get_height() / 2) - 15),
                player.get_angle(), SDL2pp::NullOpt, 0);
    } else {
        renderer.Copy(texture_storage->get_texture(skin_id),
                      SDL2pp::Rect(skin_piece.first, skin_piece.second, 32, 32),
                      SDL2pp::Point(x + (window->get_width() / 2) - 15 - reference_x,
                                    y + (window->get_height() / 2) - 15 - reference_y),
                      player.get_angle(), SDL2pp::NullOpt, 0);
    }
}

void View::SDLRenderer::render() {
    renderer.Clear();
    game_state_manager->map_function_on_players([this](const Model::Player& player) {
        render_player(player);
    });
    renderer.Present();
}

SDL2pp::Renderer* View::SDLRenderer::get_renderer() { return &renderer; }
