#ifndef CLIENT_GAME_CONTEXT_STATS_CONTEXT_H
#define CLIENT_GAME_CONTEXT_STATS_CONTEXT_H

#include <cstdint>
#include <list>

#include "common/definitions.h"
#include "entity/vertical_pane.h"
#include "handler/stats_event_handler_strategy.h"
#include "render/hud_renderer.h"
#include "render/player_renderer.h"
#include "render/stats_renderer.h"

#include "base_context.h"

namespace Controller {
class GameController;
class GameStateManager;
};  // namespace Controller

namespace Model {
class GameState;
};

namespace Context {
class StatsContext: public BaseContext {
protected:
    View::PlayerRenderer player_renderer;
    View::HUDRenderer hud_renderer;
    Controller::StatsEventHandlerStrategy strategy;
    Shared<Controller::GameStateManager> game_state_manager;

    View::VerticalPane viewport;
    View::StatsRenderer stats_renderer;

    void render(uint8_t frames) override;
    void dispatch_events() override;

public:
    explicit StatsContext(Weak<Controller::GameController> controller);

    ~StatsContext() override = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_STATS_CONTEXT_H
