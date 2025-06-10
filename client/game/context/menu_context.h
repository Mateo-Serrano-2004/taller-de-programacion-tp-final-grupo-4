#ifndef CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
#define CLIENT_GAME_CONTEXT_MENU_CONTEXT_H

#include <SDL2/SDL.h>

#include "base_context.h"

#include "handler/menu_event_handler_strategy.h"
#include "render/player_renderer.h"

#include "entity/vertical_pane.h"
#include "entity/button.h"

namespace Controller {
class GameController;
};

namespace Context {
class MenuContext: public BaseContext {
friend class Controller::MenuEventHandlerStrategy;

private:
    void trigger_buttons(Shared<SDL_Event> event);

protected:
    SDL_Event placeholder;
    Controller::MenuEventHandlerStrategy strategy;
    View::PlayerRenderer player_renderer;
    View::VerticalPane background;
    View::Button exit_button;

    void render() override;
    void dispatch_events() override;

    MenuContext(const MenuContext&) = delete;
    MenuContext& operator=(const MenuContext&) = delete;

public:
    MenuContext(Weak<Controller::GameController> controller);

    void update_size() override;

    MenuContext(MenuContext&&) = default;
    MenuContext& operator=(MenuContext&&) = default;

    ~MenuContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
