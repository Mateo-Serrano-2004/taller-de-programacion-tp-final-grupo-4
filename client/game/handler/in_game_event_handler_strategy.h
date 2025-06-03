#ifndef CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "event_handler_strategy.h"
#include "handler_state.h"

namespace Controller {
class GameController;
class GameStateManager;

class InGameEventHandlerStrategy: public EventHandlerStrategy {
private:
    Model::HandlerState handler_state;
    Weak<GameController> controller;

    void handle_movement_event(Shared<SDL_Event> event);
    void handle_window_event(Shared<SDL_Event> event);
    void handle_menu_switch_event();

    void handle_quit_event();
    void handle_keydown_event(Shared<SDL_Event> event);
    void handle_keyup_event(Shared<SDL_Event> event);

public:
    InGameEventHandlerStrategy(Weak<GameController> controller);

    void handle(Shared<SDL_Event> event) override;
    void handle_current_game_state(Shared<Controller::GameStateManager> game_state_manager);

    ~InGameEventHandlerStrategy() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
