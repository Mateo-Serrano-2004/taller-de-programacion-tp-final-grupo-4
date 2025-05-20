#ifndef CLIENT_GAME_COUNTER_STRIKE_APP_H
#define CLIENT_GAME_COUNTER_STRIKE_APP_H

#include <list>
#include <string>

#include "app.h"
#include "sdl_controller.h"
#include "window/sdl_window.h"
#include "render/sync_sdl_renderer.h"

namespace App {
    class CounterStrikeApp : public App {
    private:
        Controller::SDLController sdl_controller;
        SDLWindow sdl_window;
        View::SyncSDLRenderer sdl_renderer;

    public:
        CounterStrikeApp(const std::list<std::string>& images);

        void run() override;

        ~CounterStrikeApp() override = default;
    };
};

#endif // CLIENT_GAME_COUNTER_STRIKE_APP_H
