#ifndef CLIENT_GAME_SDL_CONTROLLER_H
#define CLIENT_GAME_SDL_CONTROLLER_H

#include <SDL2pp/SDL2pp.hh>

#include "definitions.h"

#include "controller.h"
#include "render/sync_sdl_renderer.h"
#include "event/sdl_event.h"
#include "utils/synchronizer.h"

using namespace Abstract;

namespace Controller {
    class SDLController : public Controller, public Synchronizer<SDLEvent> {
    private:
        SDL_Event placeholder;

    protected:
        void handle_event(TS<Event> event) override;

    public:
        SDLController();

        void dispatch_events() override;
    };
};

#endif // CLIENT_GAME_SDL_CONTROLLER_H
