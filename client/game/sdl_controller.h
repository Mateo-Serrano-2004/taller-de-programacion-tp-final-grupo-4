#ifndef CLIENT_GAME_SDL_CONTROLLER_H
#define CLIENT_GAME_SDL_CONTROLLER_H

#include <SDL2pp/SDL2pp.hh>

#include "definitions.h"

#include "controller.h"
#include "event/sdl_event.h"
#include "utils/synchronizer.h"

namespace Model {
    class GameState;
};
namespace Controller {
    class SDLController : public Controller {
    private:
        Model::GameState* game_state;
        SDL_Event placeholder;

    protected:
        void handle_event(TS<Event> event) override;

    public:
        SDLController(Model::GameState* game_state);

        void dispatch_events() override;
    };
};

#endif // CLIENT_GAME_SDL_CONTROLLER_H
