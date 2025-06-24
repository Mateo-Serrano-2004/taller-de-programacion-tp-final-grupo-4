#ifndef CLIENT_GAME_CONTEXT_LOADING_CONTEXT_H
#define CLIENT_GAME_CONTEXT_LOADING_CONTEXT_H

#include "common/definitions.h"
#include "entity/label.h"
#include "entity/vertical_pane.h"
#include "handler/event_handler_strategy.h"

#include "base_context.h"

namespace Controller {
class GameController;
};

namespace Context {
class LoadingContext: public BaseContext {
protected:
    Controller::EventHandlerStrategy strategy;
    View::VerticalPane viewport;
    View::Label label;

    void render(uint8_t) override;
    void dispatch_events() override;

public:
    explicit LoadingContext(Weak<Controller::GameController> controller);
    ~LoadingContext() override = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_LOADING_CONTEXT_H
