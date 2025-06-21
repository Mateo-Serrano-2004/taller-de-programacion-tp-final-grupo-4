#ifndef CLIENT_GAME_HANDLER_MENU_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_MENU_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "event_handler_strategy.h"

namespace View {
class Rendered;
};

namespace Context {
class MenuContext;
};

namespace Controller {
class GameController;

class MenuEventHandlerStrategy: public EventHandlerStrategy {
protected:
    SDL_Event placeholder;
    Context::MenuContext* context;

    void handle_switch_context_event() override;

    void handle_click();
    void handle_keydown_event();

public:
    MenuEventHandlerStrategy(Weak<GameController> controller, Context::MenuContext* context);

    void handle() override;

    ~MenuEventHandlerStrategy() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_MENU_EVENT_HANDLER_STRATEGY_H
