#ifndef CLIENT_GAME_COUNTER_STRIKE_APP_H
#define CLIENT_GAME_COUNTER_STRIKE_APP_H

#include "client/app.h"
    #include "handler/game_state_manager.h"
#include "render/sdl_renderer.h"
#include "texture/texture_storage.h"
#include "window/sdl_window.h"

#include "sdl_controller.h"

namespace Net {
class ClientProtocol;
}

namespace App {
class CounterStrikeApp: public App {
private:
    Net::ClientProtocol* protocol;
    SDLWindow sdl_window;
    Controller::GameStateManager game_state_manager;
    Controller::SDLController sdl_controller;
    View::SDLRenderer sdl_renderer;
    Model::TextureStorage texture_storage;

    void update();

public:
    explicit CounterStrikeApp(Net::ClientProtocol* protocol);

    void run() override;

    ~CounterStrikeApp() override = default;
};
};  // namespace App

#endif  // CLIENT_GAME_COUNTER_STRIKE_APP_H
