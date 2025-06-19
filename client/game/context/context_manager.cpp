#include "context_manager.h"

#include <cstdint>
#include <mutex>
#include <string>
#include <utility>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>

#include "asset/asset_manager.h"
#include "event/switch_context_event.h"

#include "base_context.h"

Shared<Context::BaseContext> Context::ContextManager::get_context(const std::string& context_name) {
    auto context = contexts.find(context_name);
    return context == contexts.end() ? nullptr : context->second;
}

void Context::ContextManager::add_context(Shared<Context::BaseContext> context) {
    contexts.insert({context->get_name(), context});
}

void Context::ContextManager::set_current_context(const std::string& context_name) {
    current_context_name = context_name;
}

void Context::ContextManager::notify_event(Shared<Model::Event> event) {
    contexts.at(current_context_name)->notify_event(event);
}

void Context::ContextManager::update_current_context(uint8_t frames) {
    if (current_context_name.empty()) {
        return;
    }
    contexts.at(current_context_name)->update(frames);
}
