#ifndef CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H
#define CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H

#include <SDL2/SDL.h>

#include "common/thread.h"
#include "common/queue.h"

#include "base_context.h"

#include "handler/in_game_event_handler_strategy.h"

namespace Controller {
class GameStateManager;
class GameController;
}

namespace Context {
class InGameContext : public BaseContext, public Thread {
protected:
    SharedQueue<SDL_Event> processor_event_queue;
    SDL_Event placeholder;
    bool running;
    Controller::InGameEventHandlerStrategy event_handler_strategy;
    Shared<Controller::GameStateManager> game_state_manager;

    void render() override;
    void dispatch_events() override;

    InGameContext(const InGameContext&) = delete;
    InGameContext& operator=(const InGameContext&) = delete;

public:
    InGameContext(Weak<Controller::GameController> controller);

    void run() override;

    InGameContext(InGameContext&&) = default;
    InGameContext& operator=(InGameContext&&) = default;

    ~InGameContext() override;
};
};

#endif // CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H
