#ifndef CLIENT_GAME_APPLICATION_H
#define CLIENT_GAME_APPLICATION_H

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLTTF.hh>

#include "common/definitions.h"
#include "context/context_manager.h"
#include "controller/base_controller.h"

namespace App {
class Application {
protected:
    SDL2pp::SDL sdl;
    SDL2pp::SDLTTF ttf;

    Shared<Context::ContextManager> context_manager;
    Shared<Controller::BaseController> controller;

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

public:
    Application();

    void launch();

    virtual ~Application() = default;
};
};  // namespace App

#endif  // CLIENT_GAME_APPLICATION_H
