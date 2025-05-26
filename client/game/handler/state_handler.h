#ifndef CLIENT_GAME_HANDLER_STATE_HANDLER_H
#define CLIENT_GAME_HANDLER_STATE_HANDLER_H

#include "keyboard_state_handler.h"
#include "mouse_state_handler.h"

namespace Model {
    class GameState;
    class Event;
}

namespace App {
    class SDLWindow;
}

namespace Controller {
    class StateHandler {
    private:
        App::SDLWindow* window;
        Model::GameState* game_state;
        SharedQueue<Model::Event>& event_queue;
        KeyboardStateHanlder keyboard_state_handler;
        MouseStateHandler mouse_state_handler;

    public:
        StateHandler(
            App::SDLWindow* window,
            Model::GameState* game_state,
            SharedQueue<Model::Event>& queue
        );

        void handle();

        ~StateHandler() = default;
    };
};

#endif // CLIENT_GAME_HANDLER_STATE_HANDLER_H
