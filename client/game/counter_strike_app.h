#ifndef CLIENT_GAME_COUNTER_STRIKE_APP_H
#define CLIENT_GAME_COUNTER_STRIKE_APP_H

#include "app.h"
#include "sdl_controller.h"
#include "model/game_state.h"
#include "window/sdl_window.h"
#include "render/sdl_renderer.h"
#include "texture/texture_storage.h"

namespace App {
    class CounterStrikeApp : public App {
    private:
        SDLWindow sdl_window;
        Model::GameState game_state;
        Controller::SDLController sdl_controller;
        View::SDLRenderer sdl_renderer;
        Model::TextureStorage texture_storage;

    public:
        CounterStrikeApp();

        void run() override;

        ~CounterStrikeApp() override = default;
    };
};

#endif // CLIENT_GAME_COUNTER_STRIKE_APP_H
