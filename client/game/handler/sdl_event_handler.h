#ifndef CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H
#define CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H

#include <atomic>

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace Model {
    class Event;
};

namespace Controller {
    class SDLEventHandler {
    private:
        SharedQueue<Model::Event>& event_queue;
        SDL_Event placeholder;

    public:
        SDLEventHandler(
            SharedQueue<Model::Event>& queue
        );

        void handle();

        ~SDLEventHandler() = default;
    };
};

#endif // CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H
