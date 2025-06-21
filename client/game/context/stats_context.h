#ifndef CLIENT_GAME_CONTEXT_STATS_CONTEXT_H
#define CLIENT_GAME_CONTEXT_STATS_CONTEXT_H

#include <cstdint>
#include <list>

#include "common/definitions.h"
#include "entity/vertical_pane.h"
#include "entity/horizontal_pane.h"
#include "entity/label.h"
#include "handler/stats_event_handler_strategy.h"
#include "render/hud_renderer.h"
#include "render/player_renderer.h"
#include "utils/line.h"

#include "base_context.h"

namespace Controller {
class GameController;
class GameStateManager;
};

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
    View::VerticalPane board;
    View::Line counter_line;
    View::Label ft_victories_label;
    View::Label st_victories_label;
    std::list<View::Line> lines;
    std::list<View::Label> players_stats;

    void update_board(const Model::GameState& game_state);

    void render(uint8_t frames) override;
    void dispatch_events() override;

public:
    StatsContext(Weak<Controller::GameController> controller);

    ~StatsContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_STATS_CONTEXT_H
