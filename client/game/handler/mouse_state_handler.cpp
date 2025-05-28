#include "mouse_state_handler.h"

#include <cstdint>
#include <cmath>

#include <SDL2/SDL.h>

#include "window/sdl_window.h"
#include "common/event/event.h"
#include "common/event/rotation_event.h"

Controller::MouseStateHandler::MouseStateHandler(
    App::SDLWindow* window,
    SharedQueue<Model::Event>& queue
): window(window), event_queue(queue),
   state(0), mouse_x(0), mouse_y(0) {}

void Controller::MouseStateHandler::handle_rotation() {
    int window_width = window->get_width();
    int window_height = window->get_height();

    int x = mouse_x - (window_width / 2);
    int y = mouse_y - (window_height / 2);

    int16_t rotation_in_deg = static_cast<int16_t>(atan2(y, x) * 180 / M_PI);

    event_queue.push(make_shared<Model::RotationEvent>(rotation_in_deg));
}

void Controller::MouseStateHandler::handle() {
    SDL_PumpEvents();

    state = SDL_GetMouseState(&mouse_x, &mouse_y);

    handle_rotation();
}
