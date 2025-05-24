#include "mouse_translator.h"

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../model/game_state.h"
#include "../event/rotation_event.h"

Model::MouseTranslator::MouseTranslator(
    Model::GameState* game_state
) : game_state(game_state) {}

Shared<Model::RotationEvent> Model::MouseTranslator::get_rotation_event() {
    int x = 0;
    int y = 0;

    (void) SDL_GetMouseState(&x, &y);

    // return make_shared<RotationEvent>((int16_t) (x) - player.get_x(), (int16_t) (y) - player.get_y());
    return make_shared<RotationEvent>((int16_t) x, (int16_t) y);
}
