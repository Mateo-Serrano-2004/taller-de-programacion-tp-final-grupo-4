#ifndef CLIENT_GAME_HANDLER_KEYBOARD_STATE_HANDLER_H
#define CLIENT_GAME_HANDLER_KEYBOARD_STATE_HANDLER_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

namespace Model {
    class Event;
};

namespace Controller {
    class KeyboardStateHanlder {
    private:
        SharedQueue<Model::Event>& event_queue;
        const Uint8* keyboard_state;

        void handle_movement();

    public:
        KeyboardStateHanlder(SharedQueue<Model::Event>& queue);

        void handle();

        ~KeyboardStateHanlder() = default;
    };
};

#endif // CLIENT_GAME_HANDLER_KEYBOARD_STATE_HANDLER_H
