#include "hud_renderer.h"

#include <iostream>
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

#include "entity/pane.h"
#include "entity/horizontal_pane.h"

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

void View::HUDRenderer::load_separator(
    std::list<View::Pane>& numbers,
    View::HorizontalPane& parent
) {
    View::Pane separator(controller);
    separator.set_draw_texture(true);
    separator.set_texture(hud_numbers);
    separator.set_texture_slice(SDL2pp::Rect(440, 0, 12, 66));
    separator.set_size(SDL2pp::Point(6, 33));
    numbers.push_back(separator);
    parent.add_child(&numbers.back());
    parent.set_width(parent.get_width() + 6);
}

void View::HUDRenderer::render_hud_symbol(std::list<View::Pane>& numbers,
                                          View::HorizontalPane& parent, uint8_t symbol_number) {
    View::Pane symbol_pane(controller);
    symbol_pane.set_draw_texture(true);
    symbol_pane.set_texture(hud_symbols);
    symbol_pane.set_texture_slice(SDL2pp::Rect(symbol_number * 64, 0, 64, 64));
    symbol_pane.set_size(SDL2pp::Point(37, 37));
    numbers.push_back(symbol_pane);
    parent.add_child(&numbers.back());
    parent.set_width(parent.get_width() + 37);
}

void View::HUDRenderer::render_number(
    std::list<View::Pane>& numbers,
    View::HorizontalPane& parent,
    uint8_t number
) {
    View::Pane number_pane(controller);
    number_pane.set_draw_texture(true);
    number_pane.set_texture(hud_numbers);
    number_pane.set_texture_slice(SDL2pp::Rect(number * 44, 0, 44, 66));
    number_pane.set_size(SDL2pp::Point(22, 33));
    numbers.push_back(number_pane);
    parent.add_child(&numbers.back());
    parent.set_width(parent.get_width() + 22);
}

void View::HUDRenderer::render_time() {
    uint16_t seconds_left = game_state_manager->get_time_left();
    auto units = get_units_of_time_left(seconds_left);

    time.clear_children();
    time.set_width(0);

    render_hud_symbol(time_numbers, time, 2);
    render_number(time_numbers, time, units[0]);
    render_number(time_numbers, time, units[1]);
    load_separator(time_numbers, time);
    render_number(time_numbers, time, units[2]);
    render_number(time_numbers, time, units[3]);
}

void View::HUDRenderer::render_life_points(Shared<RenderedPlayer> player) {
    auto units = get_units(player->get_health());

    health.clear_children();
    health.set_width(0);

    render_hud_symbol(health_numbers, health, 0);

    for (size_t i = 0; i < units.size(); i++) {
        render_number(health_numbers, health, units[i]);
    }
}

void View::HUDRenderer::render_money(Shared<View::RenderedPlayer> player) {
    auto units = get_units(player->get_money());

    money.clear_children();
    money.set_width(0);

    render_hud_symbol(money_numbers, money, 7);

    for (size_t i = 0; i < units.size(); i++) {
        render_number(money_numbers, money, units[i]);
    }
}

View::HUDRenderer::HUDRenderer(Weak<Controller::GameController> controller)
: View::Renderer(controller),
  controller(controller),
  game_state_manager(controller.lock()->get_game_state_manager()),
  hud_numbers(asset_manager->get_texture(Model::TextureID::HUD_NUMS)),
  hud_symbols(asset_manager->get_texture(Model::TextureID::HUD_SYMBOLS)),
  viewport(controller),
  time(controller),
  stats(controller),
  health(controller),
  money(controller) {
    viewport.add_child(&time);
    viewport.add_child(&stats);
    stats.add_child(&health);
    stats.add_child(&money);

    time.set_height(37);
    time.set_horizontal_alignment(0);

    stats.set_horizontal_alignment(0);
    stats.set_vertical_alignment(1);
    stats.set_gap_x(10);

    health.set_height(37);
    money.set_height(37);
}

void View::HUDRenderer::render() {
    render_time();
    auto player = game_state_manager->get_reference_player();
    if (player) {
        render_money(player);
        render_life_points(player);
    }
    viewport.render();
}
