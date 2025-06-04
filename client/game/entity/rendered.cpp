#include "rendered.h"

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "texture/texture_storage.h"
#include "controller/base_controller.h"

View::Rendered::Rendered(
    short_id_t texture_id,
    Weak<Controller::BaseController> controller
): texture_id(texture_id) {
    auto controller_locked = controller.lock();
    window = controller_locked->get_window();
    renderer = controller_locked->get_renderer();
    texture_storage = controller_locked->get_texture_storage();
}

void View::Rendered::set_new_texture_id(short_id_t new_texture_id) {
    texture_id = new_texture_id;
}
