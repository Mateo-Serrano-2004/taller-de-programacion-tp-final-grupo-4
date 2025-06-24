#include "base_context.h"

#include <cstdint>

#include <SDL2pp/Renderer.hh>

#include "controller/base_controller.h"

#include "context_manager.h"

Context::BaseContext::BaseContext(const std::string& name,
                                  Weak<Controller::BaseController> controller):
        name(name), controller(controller), renderer(controller.lock()->get_renderer()) {}

const std::string& Context::BaseContext::get_name() const { return name; }

void Context::BaseContext::notify_event(Shared<Model::Event>) {}

void Context::BaseContext::update(uint8_t frames) {
    renderer->Clear();
    dispatch_events();
    render(frames);
    renderer->Present();
}
