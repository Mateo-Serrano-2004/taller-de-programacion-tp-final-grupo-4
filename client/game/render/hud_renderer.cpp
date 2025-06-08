#include "hud_renderer.h"

#include <cstdint>
#include <list>
#include <utility>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>

#include "common/texture_id.h"

#include "controller/game_controller.h"
#include "asset/asset_manager.h"
#include "handler/game_state_manager.h"

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

void View::HUDRenderer::render_number(uint8_t number, coord_t pos_x) {
    renderer->Copy(
        *hud_numbers,
        SDL2pp::Rect(number * 44, 0, 44, 66),
        SDL2pp::Point(pos_x, 0)
    );
}

View::HUDRenderer::HUDRenderer(Weak<Controller::GameController> controller):
        View::Renderer(controller),
        game_state_manager(controller.lock()->get_game_state_manager()),
        hud_numbers(asset_manager->get_texture(Model::TextureID::HUD_NUMS)) {}

void View::HUDRenderer::render() {
    uint16_t seconds_left = game_state_manager->get_time_left();
    auto units = get_units_of_time_left(seconds_left);

    render_number(units[0], 0);
    render_number(units[1], 44);

    renderer->Copy(
        *hud_numbers,
        SDL2pp::Rect(440, 0, 12, 66),
        SDL2pp::Point(88, 0)
    );

    render_number(units[2], 100);
    render_number(units[3], 144);
}
