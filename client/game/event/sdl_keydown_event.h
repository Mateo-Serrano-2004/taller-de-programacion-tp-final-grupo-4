#ifndef CLIENT_GAME_EVENT_SDL_KEYDOWN_EVENT_H
#define CLIENT_GAME_EVENT_SDL_KEYDOWN_EVENT_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "sdl_event.h"

namespace Controller {
    class SDLKeydownEvent : public SDLEvent {

    public:
        SDLKeydownEvent(SDL_Event event) : SDLEvent(event) {}

        Sint32 get_key_sym();

        virtual ~SDLKeydownEvent() override = default;
    };
};

#endif // CLIENT_GAME_EVENT_SDL_KEYDOWN_EVENT_H
