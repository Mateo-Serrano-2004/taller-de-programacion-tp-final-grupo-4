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

    void handle_switch_context_event(Shared<SDL_Event> event) override;

    void handle_click(Shared<SDL_Event> event);
    void handle_keydown_event(Shared<SDL_Event> event);

public:
    MenuEventHandlerStrategy(
        Weak<GameController> controller,
        Context::MenuContext* context
    );

    void handle(Shared<SDL_Event> event) override;

    ~MenuEventHandlerStrategy() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_MENU_EVENT_HANDLER_STRATEGY_H
