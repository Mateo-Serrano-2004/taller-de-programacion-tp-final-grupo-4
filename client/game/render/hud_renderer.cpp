#include "hud_renderer.h"

#include <cstdint>
#include <cmath>
#include <list>
#include <utility>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>

#include "controller/game_controller.h"

#include "handler/game_state_manager.h"

#include "model/rendered_player.h"

#include "asset/asset_manager.h"
#include "asset/texture_id.h"

std::vector<uint8_t> View::HUDRenderer::get_units(uint16_t number) {
    uint8_t number_of_digits = number ? (uint8_t) (log10(number) + 1) : 1;
    std::vector<uint8_t> digits(number_of_digits);
    for (uint8_t i = 0; i < number_of_digits; i++) {
        digits[number_of_digits - i - 1] = number % 10;
        number /= 10;
    }
    return digits;
}

std::vector<uint8_t> View::HUDRenderer::get_units_of_time_left(uint16_t seconds_left) {
    std::vector<uint8_t> units_of_time_left(4);

    uint8_t minutes = seconds_left / 60;
    uint8_t seconds = seconds_left % 60;

    units_of_time_left[0] = minutes / 10;
    units_of_time_left[1] = minutes % 10;
    units_of_time_left[2] = seconds / 10;
    units_of_time_left[3] = seconds % 10;

    return units_of_time_left;
}

void View::HUDRenderer::render_hud_symbol(uint8_t symbol_number, coord_t pos_x, coord_t pos_y) {
    auto hud_symbol = asset_manager->get_texture(Model::TextureID::HUD_SYMBOLS);
    renderer->Copy(
        *hud_symbol,
        SDL2pp::Rect(symbol_number * 64, 0, 64, 64),
        SDL2pp::Rect(pos_x, pos_y, 22, 33)
    );
}

void View::HUDRenderer::render_number(uint8_t number, coord_t pos_x, coord_t pos_y) {
    renderer->Copy(
        *hud_numbers,
        SDL2pp::Rect(number * 44, 0, 44, 66),
        SDL2pp::Rect(pos_x, pos_y, 22, 33)
    );
}

void View::HUDRenderer::render_time() {
    uint16_t seconds_left = game_state_manager->get_time_left();
    auto units = get_units_of_time_left(seconds_left);

    render_number(units[0], 22, 0);
    render_number(units[1], 44, 0);

    renderer->Copy(
        *hud_numbers,
        SDL2pp::Rect(440, 0, 12, 66),
        SDL2pp::Rect(66, 0, 6, 33)
    );

    render_number(units[2], 72, 0);
    render_number(units[3], 94, 0);

    render_hud_symbol(2, 0, 0);
}

void View::HUDRenderer::render_life_points(Shared<RenderedPlayer> player) {
    auto units = get_units(player->get_health());
    for (size_t i = 0; i < units.size(); i++) {
        render_number(units[i], 22 + (i * 22), renderer->GetViewport().GetH() - 33);
    }

    render_hud_symbol(0, 0, renderer->GetViewport().GetH() - 33);
}

void View::HUDRenderer::render_money(Shared<View::RenderedPlayer> player) {
    auto units = get_units(player->get_money());
    for (size_t i = 0; i < units.size(); i++) {
        render_number(units[i], 122 + (i * 22), renderer->GetViewport().GetH() - 33);
    }

    render_hud_symbol(7, 100, renderer->GetViewport().GetH() - 33);
}

View::HUDRenderer::HUDRenderer(Weak<Controller::GameController> controller):
        View::Renderer(controller),
        game_state_manager(controller.lock()->get_game_state_manager()),
        hud_numbers(asset_manager->get_texture(Model::TextureID::HUD_NUMS)) {}

void View::HUDRenderer::render() {
    auto player = game_state_manager->get_reference_player();
    render_time();
    render_money(player);
    render_life_points(player);
}
