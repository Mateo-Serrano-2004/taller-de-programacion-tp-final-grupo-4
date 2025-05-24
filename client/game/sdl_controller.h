#ifndef CLIENT_GAME_SDL_CONTROLLER_H
#define CLIENT_GAME_SDL_CONTROLLER_H

#include <SDL2pp/SDL2pp.hh>

#include "definitions.h"

#include "controller.h"
#include "event/sdl_event.h"
#include "translators/keyboard_translator.h"
#include "translators/mouse_translator.h"

namespace App {
    class SDLWindow;
}

namespace Model {
    class GameState;
};
namespace Controller {
    class SDLController : public Controller {
    private:
        App::SDLWindow* window;
        Model::GameState* game_state;
        Model::KeyboardTranslator k_translator;
        Model::MouseTranslator m_translator;
        SDL_Event placeholder;

    protected:
        void handle_event(Shared<Event> event) override;

    public:
        SDLController(
            Model::GameState* game_state
        );

        void dispatch_events() override;
    };
};

#endif // CLIENT_GAME_SDL_CONTROLLER_H
