#ifndef CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
#define CLIENT_GAME_CONTEXT_MENU_CONTEXT_H

#include <SDL2/SDL.h>

#include "base_context.h"

#include "handler/menu_event_handler_strategy.h"

#include "entity/background.h"
#include "entity/button.h"

namespace Controller {
class GameController;
};

namespace Context {
class MenuContext: public BaseContext {
protected:
    SDL_Event placeholder;
    Controller::MenuEventHandlerStrategy event_handler_strategy;
    View::Background background;
    View::Button button;

    void render() override;
    void dispatch_events() override;

    MenuContext(const MenuContext&) = delete;
    MenuContext& operator=(const MenuContext&) = delete;

public:
    MenuContext(Weak<Controller::GameController> controller);

    MenuContext(MenuContext&&) = default;
    MenuContext& operator=(MenuContext&&) = default;


    ~MenuContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
