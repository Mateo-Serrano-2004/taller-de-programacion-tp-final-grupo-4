#include "context_manager.h"

#include <mutex>
#include <utility>
#include <string>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "base_context.h"
#include "asset/asset_manager.h"

void Context::ContextManager::add_context(Shared<Context::BaseContext> context) {
    contexts.insert({ context->get_name(), context });
}

void Context::ContextManager::set_current_context(const std::string& context_name) {
    current_context_name = context_name;
}

void Context::ContextManager::update_current_context() {
    if (current_context_name.empty()) {
        return;
    }
    contexts.at(current_context_name)->update();
}
