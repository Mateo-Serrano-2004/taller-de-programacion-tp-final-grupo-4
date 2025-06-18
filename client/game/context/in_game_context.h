#ifndef CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H
#define CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H

#include <SDL2/SDL.h>

#include "entity/pane.h"
#include "event/event.h"
#include "handler/in_game_event_handler_strategy.h"
#include "render/hud_renderer.h"
#include "render/player_renderer.h"

#include "base_context.h"

namespace Controller {
class GameController;
}

namespace Context {
class InGameContext: public BaseContext {
protected:
    SDL_Event placeholder;
    View::PlayerRenderer player_renderer;
    View::HUDRenderer hud_renderer;
    Controller::InGameEventHandlerStrategy event_handler_strategy;

    void render() override;
    void dispatch_events() override;

    InGameContext(const InGameContext&) = delete;
    InGameContext& operator=(const InGameContext&) = delete;

public:
    explicit InGameContext(Weak<Controller::GameController> controller);

    InGameContext(InGameContext&&) = default;
    InGameContext& operator=(InGameContext&&) = default;

    ~InGameContext() override = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H
