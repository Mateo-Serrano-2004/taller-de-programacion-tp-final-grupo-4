#ifndef CLIENT_GAME_SDL_CONTROLLER_H
#define CLIENT_GAME_SDL_CONTROLLER_H

#include <atomic>

#include <SDL2pp/SDL2pp.hh>

#include "common/definitions.h"
#include "handler/sdl_event_handler.h"
#include "net/event_sender.h"
#include "net/game_state_receiver.h"

#include "controller.h"

namespace Net {
class ClientProtocol;
}

namespace App {
class SDLWindow;
}

namespace Model {
class GameState;
class Event;
};  // namespace Model
namespace Controller {
class SDLController: public Controller {
private:
    std::atomic<bool> keep_running;
    Net::ClientProtocol& protocol;
    App::SDLWindow* window;
    Model::GameState* game_state;
    SDLEventHandler sdl_event_handler;
    EventSender event_sender;
    GameStateReceiver game_state_receiver;

public:
    SDLController(Net::ClientProtocol& protocol, App::SDLWindow* window,
                  Model::GameState* game_state);

    void dispatch_events() override;

    ~SDLController() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_SDL_CONTROLLER_H
