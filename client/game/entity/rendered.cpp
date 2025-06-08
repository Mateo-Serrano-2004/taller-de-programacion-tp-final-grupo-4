#include "rendered.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

View::Rendered::Rendered(
    Weak<Controller::BaseController> controller
):  draw_texture(false),
    texture_id(Model::TextureID::NO_TEXTURE),
    texture_slice(SDL2pp::NullOpt) {
    auto controller_locked = controller.lock();
    window = controller_locked->get_window();
    renderer = controller_locked->get_renderer();
    asset_manager = controller_locked->get_asset_manager();
}

bool View::Rendered::is_texture_drawn() const {
    return draw_texture;
}

Model::TextureID View::Rendered::get_texture_id() const {
    return texture_id;
}

bool View::Rendered::has_texture_slice() const {
    return (bool) texture_slice;
}

SDL2pp::Rect View::Rendered::get_texture_slice() const {
    return *texture_slice;
}

void View::Rendered::set_draw_texture(bool new_draw_texture) {
    draw_texture = new_draw_texture;
}

void View::Rendered::set_texture(Model::TextureID new_texture_id) {
    texture_id = new_texture_id;
    if (texture_id != Model::TextureID::NO_TEXTURE) {
        texture = asset_manager->get_texture(texture_id);
    }
}

void View::Rendered::set_texture_slice(const SDL2pp::Rect& new_texture_slice) {
    texture_slice = new_texture_slice;
}
