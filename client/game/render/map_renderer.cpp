#include "map_renderer.h"

#include <algorithm>
#include <cmath>

#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "controller/game_controller.h"
#include "model/game_state.h"

#include "camera.h"

SDL2pp::Rect View::MapRenderer::get_map_slice(Shared<SDL2pp::Texture> map,
                                              const View::Camera& camera) {
    auto logical_width = renderer->GetLogicalWidth();
    auto logical_height = renderer->GetLogicalHeight();
    auto camera_x = camera.get_center().GetX() + 16;
    auto camera_y = camera.get_center().GetY() + 16;
    auto map_width = map->GetWidth();
    auto map_height = map->GetHeight();

    coord_t x = camera_x - (logical_width / 2);
    coord_t y = camera_y - (logical_height / 2);

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    coord_t w = std::max(0, std::min(logical_width, map_width - x));
    coord_t h = std::max(0, std::min(logical_height, map_height - y));

    return SDL2pp::Rect(x, y, w, h);
}

SDL2pp::Rect View::MapRenderer::get_viewport_slice(const SDL2pp::Rect& map_slice,
                                                   const View::Camera& camera) {
    auto logical_width = renderer->GetLogicalWidth();
    auto logical_height = renderer->GetLogicalHeight();
    auto camera_x = camera.get_center().GetX() + 16;
    auto camera_y = camera.get_center().GetY() + 16;

    coord_t x = std::max(0, (logical_width / 2) - camera_x);
    coord_t y = std::max(0, (logical_height / 2) - camera_y);

    coord_t w = map_slice.GetW();
    coord_t h = map_slice.GetH();

    return SDL2pp::Rect(x, y, w, h);
}

View::MapRenderer::MapRenderer(Weak<Controller::GameController> controller):
        renderer(controller.lock()->get_renderer()) {}

void View::MapRenderer::render_map(const Model::GameState& game_state) {
    auto map = game_state.map;
    auto camera = game_state.camera;
    if (!map)
        return;
    auto map_slice = get_map_slice(map, camera);
    auto viewport_slice = get_viewport_slice(map_slice, camera);
    renderer->Copy(*map, map_slice, viewport_slice);
}
