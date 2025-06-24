#include "hud_renderer.h"

#include <cmath>
#include <cstdint>
#include <list>
#include <utility>
#include <vector>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "asset/texture_id.h"
#include "controller/game_controller.h"
#include "entity/horizontal_pane.h"
#include "entity/pane.h"
#include "handler/game_state_manager.h"
#include "model/game_state.h"
#include "model/rendered_player.h"
#include "utils/enum_translator.h"
#include "utils/number_texture_slicer.h"
#include "utils/pane_scalator.h"

std::vector<SDL2pp::Rect> View::HUDRenderer::get_time_slices(int seconds_left) {
    int minutes = seconds_left / 60;
    int seconds = seconds_left % 60;

    auto time_textures = View::NumberTextureSlicer::get_hud_number(minutes);
    if (time_textures.size() < 2)
        time_textures = {SDL2pp::Rect(0, 0, 44, 66), time_textures.front()};

    auto colon = View::NumberTextureSlicer::get_colon();

    auto seconds_textures = View::NumberTextureSlicer::get_hud_number(seconds);
    if (seconds_textures.size() < 2)
        seconds_textures = {SDL2pp::Rect(0, 0, 44, 66), seconds_textures.front()};

    std::vector<SDL2pp::Rect> result;
    result.reserve(time_textures.size() + 1 + seconds_textures.size());
    result.insert(result.end(), time_textures.begin(), time_textures.end());
    result.push_back(colon);
    result.insert(result.end(), seconds_textures.begin(), seconds_textures.end());

    return result;
}

void View::HUDRenderer::render_item(std::list<View::Pane>& numbers, View::HorizontalPane& parent,
                                    const SDL2pp::Rect& slice, Shared<SDL2pp::Texture> texture) {
    View::Pane number_pane(controller);
    number_pane.set_draw_texture(true);
    number_pane.set_texture(texture);
    number_pane.set_texture_slice(slice);
    number_pane.set_size(SDL2pp::Point(slice.GetW(), slice.GetH()));
    View::PaneScalator::scalate_height_with_aspect_ratio(&number_pane, 21);
    numbers.push_back(number_pane);
    parent.add_child(&numbers.back());
}

void View::HUDRenderer::render_time(uint16_t time_left) {
    auto clock_symbol = View::NumberTextureSlicer::get_symbol(2);
    auto slices = get_time_slices(time_left);

    time.clear_children();

    render_item(time_numbers, time, clock_symbol, hud_symbols);
    for (const auto& slice: slices) {
        render_item(time_numbers, time, slice, hud_numbers);
    }
}

void View::HUDRenderer::render_life_points(Shared<RenderedPlayer> player) {
    auto cross_symbol = View::NumberTextureSlicer::get_symbol(0);
    auto slices = View::NumberTextureSlicer::get_hud_number(player->get_health());

    health.clear_children();

    render_item(health_numbers, health, cross_symbol, hud_symbols);
    for (const auto& slice: slices) {
        render_item(health_numbers, health, slice, hud_numbers);
    }
}

void View::HUDRenderer::render_money(Shared<View::RenderedPlayer> player) {
    auto dollar_symbol = View::NumberTextureSlicer::get_symbol(7);
    auto slices = View::NumberTextureSlicer::get_hud_number(player->get_money());

    money.clear_children();

    render_item(money_numbers, money, dollar_symbol, hud_symbols);
    for (const auto& slice: slices) {
        render_item(money_numbers, money, slice, hud_numbers);
    }
}

View::HUDRenderer::HUDRenderer(Weak<Controller::GameController> controller):
        View::Renderer(controller),
        controller(controller),
        game_state_manager(controller.lock()->get_game_state_manager()),
        hud_numbers(asset_manager->get_texture(Model::TextureID::HUD_NUMS)),
        hud_symbols(asset_manager->get_texture(Model::TextureID::HUD_SYMBOLS)),
        viewport(controller),
        equipment_space(controller),
        equipment_renderer(controller, &equipment_space),
        time(controller),
        stats(controller),
        health(controller),
        money(controller) {
    viewport.set_horizontal_alignment(0.0f);
    viewport.add_child(&time);
    viewport.add_child(&equipment_space);
    viewport.add_child(&stats);

    stats.set_fit_to_children(true);
    stats.set_horizontal_alignment(0.0f);
    stats.set_vertical_alignment(1.0f);
    stats.add_child(&health);
    stats.add_child(&money);
    stats.set_gap_x(10);

    time.set_fit_to_children(true);
    time.set_horizontal_alignment(0.0f);

    health.set_fit_to_children(true);
    money.set_fit_to_children(true);
    equipment_space.set_height(renderer->GetLogicalHeight() - 42);
}

void View::HUDRenderer::render(const Model::GameState& game_state, uint8_t frames) {
    render_time(game_state.time_left);
    if (auto player = game_state.get_reference_player()) {
        render_money(player);
        render_life_points(player);
        equipment_renderer.render(game_state, frames);
    }
    viewport.render();
}
