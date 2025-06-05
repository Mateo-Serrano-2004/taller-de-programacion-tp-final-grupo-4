#include "rendered.h"

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

View::Rendered::Rendered(
    Model::TextureID texture_id,
    Weak<Controller::BaseController> controller
): texture_id(texture_id) {
    auto controller_locked = controller.lock();
    window = controller_locked->get_window();
    renderer = controller_locked->get_renderer();
    asset_manager = controller_locked->get_asset_manager();
}

void View::Rendered::set_new_texture_id(Model::TextureID new_texture_id) {
    texture_id = new_texture_id;
}
