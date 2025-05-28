#include "state_handler.h"

#include <SDL2/SDL.h>

#include "window/sdl_window.h"
#include "common/model/game_state.h"
#include "common/event/event.h"

Controller::StateHandler::StateHandler(
    App::SDLWindow* window,
    Model::GameState* game_state,
    SharedQueue<Model::Event>& queue
):  window(window),
    game_state(game_state),
    event_queue(queue),
    keyboard_state_handler(queue),
    mouse_state_handler(window, queue) {}

void Controller::StateHandler::handle() {
    keyboard_state_handler.handle();
    mouse_state_handler.handle();
}
