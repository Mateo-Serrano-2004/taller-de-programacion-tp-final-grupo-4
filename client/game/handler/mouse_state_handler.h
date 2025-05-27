#ifndef CLIENT_GAME_HANDLER_MOUSE_STATE_HANDLER_H
#define CLIENT_GAME_HANDLER_MOUSE_STATE_HANDLER_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace App {
    class SDLWindow;
}

namespace Model {
    class Event;
}

namespace Controller {
    class MouseStateHandler {
    private:
        App::SDLWindow* window;
        SharedQueue<Model::Event>& event_queue;
        Uint32 state;
        int mouse_x;
        int mouse_y;

        void handle_rotation();

    public:
        MouseStateHandler(
            App::SDLWindow* window,
            SharedQueue<Model::Event>& queue
        );

        void handle();

        ~MouseStateHandler() = default;
    };
};

#endif // CLIENT_GAME_HANDLER_MOUSE_STATE_HANDLER_H
