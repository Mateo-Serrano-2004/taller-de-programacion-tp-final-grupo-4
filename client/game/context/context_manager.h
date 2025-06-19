#ifndef CLIENT_GAME_CONTEXT_CONTEXT_MANAGER_H
#define CLIENT_GAME_CONTEXT_CONTEXT_MANAGER_H

#include <map>
#include <mutex>
#include <string>

#include "common/definitions.h"
#include "event/event.h"

namespace Model {
class AssetManager;
};

namespace SDL2pp {
class Window;
class Renderer;
};  // namespace SDL2pp

namespace Context {
class BaseContext;

class ContextManager {
protected:
    std::mutex mutex;
    std::map<std::string, Shared<BaseContext>> contexts;
    std::string current_context_name;

    ContextManager(const ContextManager&) = delete;
    ContextManager& operator=(const ContextManager&) = delete;

public:
    ContextManager() = default;

    Shared<BaseContext> get_context(const std::string& context_name);
    void add_context(Shared<BaseContext> context);
    void set_current_context(const std::string& context_name);

    void notify_event(Shared<Model::Event> event);
    void update_current_context(uint8_t frames);

    ContextManager(ContextManager&&) = default;
    ContextManager& operator=(ContextManager&&) = default;

    ~ContextManager() = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_CONTEXT_MANAGER_H
