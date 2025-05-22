#ifndef CLIENT_GAME_EVENT_SDL_EVENT_H
#define CLIENT_GAME_EVENT_SDL_EVENT_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/game/event/event.h"

namespace Controller {
    class SDLEvent : public Event {
    protected:
        SDL_Event event;
    
    public:
        SDLEvent(SDL_Event event) : Event(), event(event) {}

        Uint32 type() const;

        virtual ~SDLEvent() override = default;
    };
};

#endif // CLIENT_GAME_EVENT_SDL_EVENT_H
