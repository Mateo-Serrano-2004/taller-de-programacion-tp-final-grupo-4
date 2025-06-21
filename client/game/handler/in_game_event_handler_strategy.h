#ifndef CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "event_handler_strategy.h"
#include "handler_state.h"
#include "movement_handler.h"
#include "weapon_handler.h"

namespace Controller {
class GameController;
class GameStateManager;

class InGameEventHandlerStrategy: public EventHandlerStrategy {
protected:
    Shared<GameStateManager> game_state_manager;
    MovementHandler movement_handler;
    WeaponHandler weapon_handler;
    Model::HandlerState handler_state;

    void handle_switch_context_event() override;
    void handle_keydown_event();

public:
    explicit InGameEventHandlerStrategy(Weak<GameController> controller);

    void handle() override;
    void handle_current_game_state();

    void update_on_switch_context();

    ~InGameEventHandlerStrategy() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
