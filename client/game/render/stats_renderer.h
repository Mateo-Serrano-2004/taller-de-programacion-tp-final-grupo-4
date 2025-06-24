#ifndef CLIENT_GAME_RENDER_STATS_RENDERER_H
#define CLIENT_GAME_RENDER_STATS_RENDERER_H

#include <list>

#include "entity/horizontal_pane.h"
#include "entity/label.h"
#include "entity/vertical_pane.h"
#include "utils/stat_line.h"

namespace Controller {
class GameController;
};

namespace Model {
struct GameState;
};

namespace View {
class StatsRenderer {
private:
    Weak<Controller::GameController> controller;
    Pane* viewport;
    HorizontalPane stats;
    VerticalPane first_team_stats;
    Label first_team_victories;
    StatLine first_stats_indicator;
    StatLine second_stats_indicator;
    Pane separator;
    VerticalPane second_team_stats;
    Label second_team_victories;
    std::list<StatLine> first_team_stats_items;
    std::list<StatLine> second_team_stats_items;

    void clear();
    void add_victories(const Model::GameState& game_state);

public:
    StatsRenderer(Weak<Controller::GameController> controller, Pane* viewport);

    void render(const Model::GameState& game_state);

    ~StatsRenderer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_STATS_RENDERER_H
