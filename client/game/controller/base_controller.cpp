#include "base_controller.h"

#include <utility>
#include <memory>
#include <iostream>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "common/event_type.h"

#include "texture/texture_storage.h"
#include "event/event.h"
#include "context/context_manager.h"

Controller::BaseController::BaseController(
    Shared<SDL2pp::Window> window,
    Shared<SDL2pp::Renderer> renderer,
    Shared<Model::TextureStorage> texture_storage,
    Shared<Context::ContextManager> context_manager
): window(window), renderer(renderer), texture_storage(texture_storage), context_manager(context_manager) {
    start();
}

Weak<SDL2pp::Window> Controller::BaseController::get_window() {
    return Weak<SDL2pp::Window>(window);
}

Weak<SDL2pp::Renderer> Controller::BaseController::get_renderer() {
    return Weak<SDL2pp::Renderer>(renderer);
}

Weak<Model::TextureStorage> Controller::BaseController::get_texture_storage() {
    return Weak<Model::TextureStorage>(texture_storage);
}

Weak<Context::ContextManager> Controller::BaseController::get_context_manager() {
    return Weak<Context::ContextManager>(context_manager);
}

void Controller::BaseController::handle_event(Shared<Model::Event> event) {
    processor_event_queue.push(event);
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
