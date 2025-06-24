#ifndef CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H
#define CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H

#include <cstdint>

#include "common/definitions.h"
#include "entity/horizontal_pane.h"
#include "entity/label.h"
#include "entity/vertical_pane.h"
#include "event/event.h"
#include "handler/in_game_event_handler_strategy.h"
#include "model/game_state.h"
#include "render/hud_renderer.h"
#include "render/player_renderer.h"

#include "base_context.h"

namespace Controller {
class GameController;
class GameStateManager;
}  // namespace Controller

namespace Context {
class InGameContext: public BaseContext {
    friend class Controller::InGameEventHandlerStrategy;

protected:
    Model::GameState current_game_state;
    View::PlayerRenderer player_renderer;
    View::HUDRenderer hud_renderer;
    Controller::InGameEventHandlerStrategy strategy;
    Shared<Controller::GameStateManager> game_state_manager;

    void render(uint8_t frames) override;
    void dispatch_events() override;

    InGameContext(const InGameContext&) = delete;
    InGameContext& operator=(const InGameContext&) = delete;

public:
    explicit InGameContext(Weak<Controller::GameController> controller);

    void notify_event(Shared<Model::Event> event) override;

    InGameContext(InGameContext&&) = default;
    InGameContext& operator=(InGameContext&&) = default;

    ~InGameContext() override = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_IN_GAME_CONTEXT_H
