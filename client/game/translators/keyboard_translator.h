#ifndef CLIENT_GAME_DEVICES_KEYBOARD_TRANSLATOR_H
#define CLIENT_GAME_DEVICES_KEYBOARD_TRANSLATOR_H

#include <list>

#include "../definitions.h"
#include "../event/movement_event.h"
#include "../event/rotation_event.h"

namespace Model {
    class KeyboardTranslator {
    public:
        KeyboardTranslator() = default;

        Shared<MovementEvent> get_movement_event();

        ~KeyboardTranslator() = default;
    };
};

#endif // CLIENT_GAME_DEVICES_KEYBOARD_TRANSLATOR_H
