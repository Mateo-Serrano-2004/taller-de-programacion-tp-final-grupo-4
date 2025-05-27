#ifndef CLIENT_GAME_SDL_CONTROLLER_H
#define CLIENT_GAME_SDL_CONTROLLER_H

#include <SDL2pp/SDL2pp.hh>

#include "common/definitions.h"

#include "controller.h"
#include "handler/state_handler.h"
#include "handler/sdl_event_handler.h"

namespace App {
    class SDLWindow;
}

namespace Model {
    class GameState;
    class Event;
};
namespace Controller {
    class SDLController : public Controller {
    private:
        App::SDLWindow* window;
        Model::GameState* game_state;
        SDLEventHandler sdl_event_handler;
        StateHandler state_handler;

    protected:
        void handle_event(Shared<Model::Event> event) override;

    public:
        SDLController(
            App::SDLWindow* window,
            Model::GameState* game_state
        );

        void dispatch_events() override;
    };
};

#endif // CLIENT_GAME_SDL_CONTROLLER_H
