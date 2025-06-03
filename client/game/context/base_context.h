#ifndef CLIENT_GAME_CONTEXT_BASE_CONTEXT_H
#define CLIENT_GAME_CONTEXT_BASE_CONTEXT_H

#include <list>
#include <string>

#include "common/definitions.h"

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

    virtual void render() = 0;
    virtual void dispatch_events() = 0;

    BaseContext(const BaseContext&) = delete;
    BaseContext& operator=(const BaseContext&) = delete;

public:
    BaseContext(const std::string& name, Weak<Controller::BaseController> controller);

    const std::string& get_name() const;
    
    void update();
    
    BaseContext(BaseContext&&) = default;
    BaseContext& operator=(BaseContext&&) = default;

    virtual ~BaseContext() = default;
};
};

#endif // CLIENT_GAME_CONTEXT_BASE_CONTEXT_H
