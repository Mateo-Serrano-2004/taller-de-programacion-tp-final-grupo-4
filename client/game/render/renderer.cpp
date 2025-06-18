#include "renderer.h"

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

View::Renderer::Renderer(Weak<Controller::BaseController> controller) {
    auto controller_locked = controller.lock();
    window = controller_locked->get_window();
    renderer = controller_locked->get_renderer();
    asset_manager = controller_locked->get_asset_manager();
}
