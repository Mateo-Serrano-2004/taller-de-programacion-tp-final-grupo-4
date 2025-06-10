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
protected:
    Shared<GameStateManager> game_state_manager;

    Model::HandlerState handler_state;

    void handle_movement_event(Shared<SDL_Event> event);
    void handle_window_event(Shared<SDL_Event> event);
    void handle_switch_weapon_event(Shared<SDL_Event> event);
    void handle_switch_context_event(Shared<SDL_Event> event) override;

    void handle_stop_movement_event(Shared<SDL_Event> event);
    void handle_stop_switching_weapon_event();

    void handle_keydown_event(Shared<SDL_Event> event);
    void handle_keyup_event(Shared<SDL_Event> event);

public:
    InGameEventHandlerStrategy(Weak<GameController> controller);

    void handle(Shared<SDL_Event> event) override;
    void handle_current_game_state();

    ~InGameEventHandlerStrategy() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
