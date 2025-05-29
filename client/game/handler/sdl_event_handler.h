#ifndef CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H
#define CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H

#include <atomic>

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "handler_state.h"

namespace Model {
class Event;
};

namespace Controller {
class SDLEventHandler {
private:
    SharedQueue<Model::Event>& event_queue;
    Model::HandlerState handler_state;
    SDL_Event placeholder;

    void handle_quit_event();
    void handle_keydown_event();
    void handle_keyup_event();

public:
    explicit SDLEventHandler(SharedQueue<Model::Event>& queue);

    void handle();

    ~SDLEventHandler() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H
