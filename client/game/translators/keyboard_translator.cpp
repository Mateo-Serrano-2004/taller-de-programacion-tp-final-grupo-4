#include "keyboard_translator.h"

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../event/movement_event.h"

Shared<Model::MovementEvent> Model::KeyboardTranslator::get_movement_event() {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    int8_t x_movement = 0;
    int8_t y_movement = 0;
    int8_t speed_type = 0;

    // Speed modifiers
    if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) speed_type++;
    if (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]) speed_type--;

    // Displacement buttons
    if (state[SDL_SCANCODE_W]) y_movement--;
    if (state[SDL_SCANCODE_A]) x_movement--;
    if (state[SDL_SCANCODE_S]) y_movement++;
    if (state[SDL_SCANCODE_D]) x_movement++;

    if (x_movement || y_movement || speed_type) {
        return make_shared<MovementEvent>(x_movement, y_movement, speed_type);
    }
    return nullptr;
}
