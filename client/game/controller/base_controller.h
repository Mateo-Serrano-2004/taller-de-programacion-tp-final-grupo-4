#ifndef CLIENT_GAME_CONTROLLER_BASE_CONTROLLER_H
#define CLIENT_GAME_CONTROLLER_BASE_CONTROLLER_H

#include "common/definitions.h"

namespace SDL2pp {
class Window;
class Renderer;
};  // namespace SDL2pp

namespace Context {
class ContextManager;
};

namespace Model {
class Event;
class AssetManager;
class AssetLoader;
};  // namespace Model

namespace Controller {
class BaseController {
protected:
    SharedQueue<Model::Event> processor_event_queue;
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::AssetManager> asset_manager;
    Shared<Model::AssetLoader> asset_loader;
    Shared<Context::ContextManager> context_manager;

    BaseController(const BaseController&) = delete;
    BaseController& operator=(const BaseController&) = delete;

    virtual void process_event(Shared<Model::Event> event) = 0;

public:
    BaseController(Shared<SDL2pp::Window> window, Shared<SDL2pp::Renderer> renderer,
                   Shared<Model::AssetManager> asset_manager,
                   Shared<Model::AssetLoader> asset_loader,
                   Shared<Context::ContextManager> context_manager);

    Shared<SDL2pp::Window> get_window();
    Shared<SDL2pp::Renderer> get_renderer();
    Shared<Model::AssetManager> get_asset_manager();

    void handle_events();
    void push_event(Shared<Model::Event> event);

    BaseController(BaseController&&) = default;
    BaseController& operator=(BaseController&&) = default;

    virtual ~BaseController() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_CONTROLLER_BASE_CONTROLLER_H
