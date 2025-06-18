#include "textured.h"

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

View::Textured::Textured(Weak<Controller::BaseController> controller):
        draw_texture(false),
        texture(nullptr),
        texture_slice(SDL2pp::NullOpt),
        asset_manager(controller.lock()->get_asset_manager()) {}

bool View::Textured::is_texture_drawn() const { return draw_texture; }

SDL2pp::Optional<SDL2pp::Rect> View::Textured::get_texture_slice() const { return texture_slice; }

void View::Textured::set_draw_texture(bool new_draw_texture) { draw_texture = new_draw_texture; }

void View::Textured::set_texture(Shared<SDL2pp::Texture> new_texture) { texture = new_texture; }

void View::Textured::set_texture(Model::TextureID new_texture_id) {
    if (new_texture_id != Model::TextureID::NO_TEXTURE) {
        texture = asset_manager->get_texture(new_texture_id);
    } else {
        texture = nullptr;
    }
}

void View::Textured::set_texture_slice(const SDL2pp::Rect& new_texture_slice) {
    texture_slice = new_texture_slice;
}

void View::Textured::reset_texture_slice() { texture_slice = SDL2pp::NullOpt; }
