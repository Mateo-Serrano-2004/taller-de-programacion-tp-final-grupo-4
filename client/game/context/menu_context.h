#ifndef CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
#define CLIENT_GAME_CONTEXT_MENU_CONTEXT_H

#include <SDL2/SDL.h>

#include "base_context.h"

#include "handler/menu_event_handler_strategy.h"
#include "render/player_renderer.h"

#include "entity/pane.h"
#include "entity/exit_button.h"

namespace Controller {
class GameController;
};

namespace Context {
class MenuContext: public BaseContext {
protected:
    SDL_Event placeholder;
    Controller::MenuEventHandlerStrategy event_handler_strategy;
    View::PlayerRenderer player_renderer;
    View::Pane background;
    View::ExitButton exit_button;

    void render() override;
    void dispatch_events() override;

    MenuContext(const MenuContext&) = delete;
    MenuContext& operator=(const MenuContext&) = delete;

    void size_pane_relatively_to_parent(View::Pane& pane, double portion_x, double portion_y);
    void place_pane_relatively_to_parent(View::Pane& pane, double portion_x, double portion_y);

public:
    MenuContext(Weak<Controller::GameController> controller);

    MenuContext(MenuContext&&) = default;
    MenuContext& operator=(MenuContext&&) = default;


    ~MenuContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
