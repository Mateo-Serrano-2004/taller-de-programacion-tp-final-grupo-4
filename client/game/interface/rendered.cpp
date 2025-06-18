#include "rendered.h"

#include <SDL2pp/Renderer.hh>

#include "controller/base_controller.h"

View::Rendered::Rendered(Weak<Controller::BaseController> controller):
        renderer(controller.lock()->get_renderer()) {}
