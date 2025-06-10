#include "base_controller.h"

#include <utility>
#include <memory>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "common/event_type.h"

#include "asset/asset_manager.h"
#include "event/event.h"
#include "event/switch_context_event.h"
#include "context/context_manager.h"
#include "exception/closed_window.h"

Controller::BaseController::BaseController(
    Shared<SDL2pp::Window> window,
    Shared<SDL2pp::Renderer> renderer,
    Shared<Model::AssetManager> asset_manager,
    Shared<Context::ContextManager> context_manager
): window(window), renderer(renderer), asset_manager(asset_manager), context_manager(context_manager) {
    start();
}

Shared<SDL2pp::Window> Controller::BaseController::get_window() {
    return window;
}

Shared<SDL2pp::Renderer> Controller::BaseController::get_renderer() {
    return renderer;
}

Shared<Model::AssetManager> Controller::BaseController::get_asset_manager() {
    return asset_manager;
}

Weak<Context::ContextManager> Controller::BaseController::get_context_manager() {
    return Weak<Context::ContextManager>(context_manager);
}

void Controller::BaseController::handle_event(Shared<Model::Event> event) {
    if (event->get_type() == Model::EventType::SWITCH_CONTEXT) {
        auto switch_context_event = std::static_pointer_cast<Model::SwitchContextEvent>(event);
        context_manager->set_current_context(switch_context_event->get_new_context_name());
    } else if (event->get_type() == Model::EventType::WINDOW_RESIZE) {
        context_manager->update_context_size();
    } else {
        processor_event_queue.push(event);

        if (event->get_type() == Model::EventType::QUIT) {
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }
}

void Controller::BaseController::run() {
    bool running = true;
    while (running) {
        // Nor the main thread nor the event processor
        // closes the queue, so we can safely
        // call pop() without checking if the queue is closed.

        Shared<Model::Event> event = processor_event_queue.pop();

        if (event->get_type() == Model::EventType::QUIT) {
            running = false;
        }

        process_event(event);
    }
}

Controller::BaseController::~BaseController() {
    stop();
    join();
}
