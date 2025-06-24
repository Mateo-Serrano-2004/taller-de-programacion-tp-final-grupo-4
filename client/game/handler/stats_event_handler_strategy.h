#ifndef CLIENT_GAME_HANDLER_STATS_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_STATS_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "event_handler_strategy.h"
#include "mouse_movement_handler.h"
#include "movement_handler.h"

namespace Controller {
class GameController;

class StatsEventHandlerStrategy: public EventHandlerStrategy {
protected:
    MovementHandler movement_handler;
    MouseMovementHandler mouse_movement_handler;

    void handle_switch_context_event() override;

public:
    explicit StatsEventHandlerStrategy(Weak<GameController> controller);

    void handle() override;
    void handle_current_game_state();

    void update_on_switch_context();

    ~StatsEventHandlerStrategy() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_STATS_EVENT_HANDLER_STRATEGY_H
