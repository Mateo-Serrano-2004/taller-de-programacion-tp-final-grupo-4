#ifndef CLIENT_GAME_SDL_CONTROLLER_H
#define CLIENT_GAME_SDL_CONTROLLER_H

#include <atomic>

#include <SDL2pp/SDL2pp.hh>

#include "common/definitions.h"
#include "event/event.h"
#include "handler/sdl_event_handler.h"
#include "net/event_sender.h"
#include "net/game_state_receiver.h"

namespace Net {
class ClientProtocol;
}

namespace App {
class SDLWindow;
}

namespace Model {
class Event;
};  // namespace Model
namespace Controller {
class GameStateManager;

class SDLController {
private:
    Net::ClientProtocol* protocol;
    App::SDLWindow* window;
    GameStateManager* game_state_manager;
    SharedQueue<Model::Event> dispatched_events_queue;
    SDLEventHandler sdl_event_handler;
    EventSender event_sender;
    GameStateReceiver game_state_receiver;

public:
    SDLController(Net::ClientProtocol* protocol, App::SDLWindow* window,
                  GameStateManager* game_state_manager);

    void dispatch_events();

    ~SDLController() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_SDL_CONTROLLER_H
