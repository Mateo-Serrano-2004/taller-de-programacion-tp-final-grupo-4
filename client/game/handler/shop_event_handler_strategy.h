#ifndef CLIENT_GAME_HANDLER_SHOP_EVENT_HANDLER_STRATEGY_H
#define CLIENT_GAME_HANDLER_SHOP_EVENT_HANDLER_STRATEGY_H

#include "common/definitions.h"

#include "event_handler_strategy.h"

namespace Context {
class ShopContext;
};

namespace Controller {
class GameController;

class ShopEventHandlerStrategy: public EventHandlerStrategy {
private:
    Context::ShopContext* context;

    void handle_switch_context_event() override;
    void handle_click();

public:
    ShopEventHandlerStrategy(Weak<GameController> controller, Context::ShopContext* context);

    void handle() override;

    ~ShopEventHandlerStrategy() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_SHOP_EVENT_HANDLER_STRATEGY_H
