#ifndef CLIENT_GAME_DEVICES_MOUSE_TRANSLATOR_H
#define CLIENT_GAME_DEVICES_MOUSE_TRANSLATOR_H

#include <list>

#include "../definitions.h"
#include "../event/rotation_event.h"

namespace Model {
    class GameState;

    class MouseTranslator {
    private:
        GameState* game_state;

    public:
        MouseTranslator(GameState* game_state);

        Shared<RotationEvent> get_rotation_event();

        ~MouseTranslator() = default;
    };
};

#endif // CLIENT_GAME_DEVICES_MOUSE_TRANSLATOR_H
