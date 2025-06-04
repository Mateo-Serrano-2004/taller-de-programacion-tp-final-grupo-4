#include "renderer.h"

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "controller/base_controller.h"
#include "texture/texture_storage.h"

View::Renderer::Renderer(Weak<Controller::BaseController> controller) {
    auto controller_locked = controller.lock();
    window = controller_locked->get_window();    
    renderer = controller_locked->get_renderer();    
    texture_storage = controller_locked->get_texture_storage();    
}
