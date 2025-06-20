#include "base_controller.h"

#include <memory>
#include <utility>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>

#include "asset/asset_loader.h"
#include "asset/asset_manager.h"
#include "client/exception/closed_app.h"
#include "common/event_type.h"
#include "context/context_manager.h"
#include "event/event.h"
#include "event/switch_context_event.h"

Controller::BaseController::BaseController(Shared<SDL2pp::Window> window,
                                           Shared<SDL2pp::Renderer> renderer,
                                           Shared<Model::AssetManager> asset_manager,
                                           Shared<Model::AssetLoader> asset_loader,
                                           Shared<Context::ContextManager> context_manager):
        window(window),
        renderer(renderer),
        asset_manager(asset_manager),
        asset_loader(asset_loader),
        context_manager(context_manager) {}

Shared<SDL2pp::Window> Controller::BaseController::get_window() { return window; }

Shared<SDL2pp::Renderer> Controller::BaseController::get_renderer() { return renderer; }

Shared<Model::AssetManager> Controller::BaseController::get_asset_manager() {
    return asset_manager;
}

void Controller::BaseController::handle_events() {
    Shared<Model::Event> event;
    while (processor_event_queue.try_pop(event)) {
        process_event(event);
    }
}

void Controller::BaseController::push_event(Shared<Model::Event> event) {
    processor_event_queue.push(event);
}
