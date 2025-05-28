#ifndef CLIENT_GAME_COUNTER_STRIKE_APP_H
#define CLIENT_GAME_COUNTER_STRIKE_APP_H

#include "sdl_controller.h"
#include "window/sdl_window.h"
#include "render/sdl_renderer.h"
#include "texture/texture_storage.h"
#include "client/app.h"
#include "common/model/game_state.h"

namespace Net {
    class ClientProtocol;
}

namespace App {
    class CounterStrikeApp : public App {
    private:
        Net::ClientProtocol& protocol;
        SDLWindow sdl_window;
        Model::GameState game_state;
        Controller::SDLController sdl_controller;
        View::SDLRenderer sdl_renderer;
        Model::TextureStorage texture_storage;

    public:
        CounterStrikeApp(Net::ClientProtocol& protocol);

        void run() override;

        ~CounterStrikeApp() override = default;
    };
};

#endif // CLIENT_GAME_COUNTER_STRIKE_APP_H
