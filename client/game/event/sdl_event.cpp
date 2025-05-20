#include "client/game/event/sdl_event.h"

Uint32 Controller::SDLEvent::type() const {
    return event.type;
}
