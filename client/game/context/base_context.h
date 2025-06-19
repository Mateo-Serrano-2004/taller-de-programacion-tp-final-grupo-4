#ifndef CLIENT_GAME_CONTEXT_BASE_CONTEXT_H
#define CLIENT_GAME_CONTEXT_BASE_CONTEXT_H

#include <cstdint>
#include <list>
#include <string>

#include "common/definitions.h"
#include "event/event.h"

namespace Controller {
class BaseController;
}

namespace SDL2pp {
class Renderer;
};

namespace Context {
class ContextManager;

class BaseContext {
protected:
    std::string name;
    Weak<Controller::BaseController> controller;
    Shared<SDL2pp::Renderer> renderer;

    virtual void render(uint8_t frames) = 0;
    virtual void dispatch_events() = 0;

    BaseContext(const BaseContext&) = delete;
    BaseContext& operator=(const BaseContext&) = delete;

public:
    BaseContext(const std::string& name, Weak<Controller::BaseController> controller);

    const std::string& get_name() const;

    virtual void notify_event(Shared<Model::Event> event);
    void update(uint8_t frames);

    BaseContext(BaseContext&&) = default;
    BaseContext& operator=(BaseContext&&) = default;

    virtual ~BaseContext() = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_BASE_CONTEXT_H
