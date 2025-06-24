#ifndef CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H

#include <string>

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "event_handler_strategy.h"
#include "mouse_movement_handler.h"
#include "movement_handler.h"
#include "weapon_handler.h"

namespace Context {
class InGameContext;
};

namespace Controller {
class GameController;

class InGameEventHandlerStrategy: public EventHandlerStrategy {
protected:
    MovementHandler movement_handler;
    WeaponHandler weapon_handler;
    MouseMovementHandler mouse_movement_handler;
    Context::InGameContext* context;

    void handle_switch_context_event() override;

public:
    InGameEventHandlerStrategy(Weak<GameController> controller, Context::InGameContext* context);

    void handle() override;
    void handle_current_game_state();

    void update_on_switch_context(const std::string& new_context_name);

    ~InGameEventHandlerStrategy() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_IN_GAME_EVENT_HANDLER_STRATEGY_H
