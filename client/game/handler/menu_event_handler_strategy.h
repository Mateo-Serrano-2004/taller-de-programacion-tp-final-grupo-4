#ifndef CLIENT_GAME_HANDLER_MENU_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_MENU_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "event_handler_strategy.h"

namespace Controller {
class GameController;

class MenuEventHandlerStrategy: public EventHandlerStrategy {
protected:
    SDL_Event placeholder;

    void handle_switch_context_event(Shared<SDL_Event> event) override;

    void handle_keydown_event(Shared<SDL_Event> event);

public:
    MenuEventHandlerStrategy(Weak<GameController> controller);

    void handle(Shared<SDL_Event> event) override;

    ~MenuEventHandlerStrategy() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_MENU_EVENT_HANDLER_STRATEGY_H
