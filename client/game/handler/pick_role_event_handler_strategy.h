#ifndef CLIENT_GAME_HANDLER_PICK_ROLE_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_PICK_ROLE_EVENT_HANDLER_STRATEGY_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "event_handler_strategy.h"

namespace Context {
class PickRoleContext;
};

namespace Controller {
class GameController;

class PickRoleEventHandlerStrategy: public EventHandlerStrategy {
protected:
    Context::PickRoleContext* context;

    void handle_switch_context_event(Shared<SDL_Event> event) override;

public:
    PickRoleEventHandlerStrategy(
        Weak<GameController> controller,
        Context::PickRoleContext* context
    );

    void handle(Shared<SDL_Event> event) override;

    ~PickRoleEventHandlerStrategy() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_PICK_ROLE_EVENT_HANDLER_STRATEGY_H
