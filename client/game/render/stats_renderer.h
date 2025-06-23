#ifndef CLIENT_GAME_RENDER_STATS_RENDERER_H
#define CLIENT_GAME_RENDER_STATS_RENDERER_H

#include <list>

#include "entity/vertical_pane.h"
#include "entity/horizontal_pane.h"
#include "entity/label.h"
#include "utils/line.h"

namespace View {
class StatsRenderer {
private:
    HorizontalPane stats;
    VerticalPane first_team_stats;
    VerticalPane second_team_stats;
    std::list<HorizontalPane> first_team_stats_items;
    std::list<HorizontalPane> second_team_stats_items;

public:
    StatsRenderer();
    ~StatsRenderer();
};
};

#endif // CLIENT_GAME_RENDER_STATS_RENDERER_H
