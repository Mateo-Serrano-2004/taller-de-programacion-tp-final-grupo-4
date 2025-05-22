#include "sdl_keydown_event.h"

Sint32 Controller::SDLKeydownEvent::get_key_sym() {
    return event.key.keysym.sym;
}
