#include "keyboard_state_handler.h"

#include <SDL2/SDL.h>

#include "common/event/event.h"
#include "common/event/movement_event.h"

void Controller::KeyboardStateHanlder::handle_movement() {
    int8_t x_movement = 0;
    int8_t y_movement = 0;
    int8_t speed_type = 0;

    // Speed modifiers
    if (keyboard_state[SDL_SCANCODE_LSHIFT] || keyboard_state[SDL_SCANCODE_RSHIFT]) speed_type++;
    if (keyboard_state[SDL_SCANCODE_LCTRL] || keyboard_state[SDL_SCANCODE_RCTRL]) speed_type--;

    // Displacement buttons
    if (keyboard_state[SDL_SCANCODE_W]) y_movement--;
    if (keyboard_state[SDL_SCANCODE_A]) x_movement--;
    if (keyboard_state[SDL_SCANCODE_S]) y_movement++;
    if (keyboard_state[SDL_SCANCODE_D]) x_movement++;

    event_queue.push(make_shared<Model::MovementEvent>(x_movement, y_movement, speed_type));
}

Controller::KeyboardStateHanlder::KeyboardStateHanlder(SharedQueue<Model::Event>& queue)
: event_queue(queue), keyboard_state(nullptr) {}

void Controller::KeyboardStateHanlder::handle() {
    SDL_PumpEvents();

    keyboard_state = SDL_GetKeyboardState(nullptr);

    handle_movement();
}
