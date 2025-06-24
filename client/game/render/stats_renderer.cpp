#include "stats_renderer.h"

#include <string>

#include "common/team.h"
#include "controller/game_controller.h"
#include "model/game_state.h"
#include "model/rendered_player.h"

void View::StatsRenderer::clear() {
    first_team_stats.clear_children();
    second_team_stats.clear_children();
    first_team_stats_items.clear();
    second_team_stats_items.clear();
}

void View::StatsRenderer::add_victories(const Model::GameState& game_state) {
    first_team_stats.add_child(&first_team_victories);
    first_team_victories.set_text(std::to_string(game_state.first_team_victories) + " victories");

    second_team_stats.add_child(&second_team_victories);
    second_team_victories.set_text(std::to_string(game_state.second_team_victories) + " victories");
}

View::StatsRenderer::StatsRenderer(Weak<Controller::GameController> controller,
                                   View::Pane* viewport):
        controller(controller),
        viewport(viewport),
        stats(controller),
        first_team_stats(controller),
        first_team_victories(controller),
        first_stats_indicator(controller),
        second_stats_indicator(controller),
        separator(controller),
        second_team_stats(controller),
        second_team_victories(controller) {
    viewport->add_child(&stats);
    stats.add_child(&first_team_stats);
    stats.add_child(&separator);
    stats.add_child(&second_team_stats);
    stats.set_fit_to_children(true);
    stats.set_vertical_alignment(0.0f);
    stats.set_horizontal_alignment(0.0f);

    first_team_stats.set_vertical_alignment(0.0f);
    first_team_stats.set_height(130);
    first_team_stats.set_width(200);
    first_team_stats.set_background_color(31, 45, 31, 255);
    first_team_stats.set_draw_background(true);

    second_team_stats.set_vertical_alignment(0.0f);
    second_team_stats.set_height(130);
    second_team_stats.set_width(200);
    second_team_stats.set_background_color(31, 45, 31, 255);
    second_team_stats.set_draw_background(true);

    first_stats_indicator.set_all_fonts_size(8);
    first_stats_indicator.set_line_height(9);
    first_stats_indicator.set_name("Name");
    first_stats_indicator.set_kills("Kills");
    first_stats_indicator.set_deaths("Deaths");

    second_stats_indicator.set_all_fonts_size(8);
    second_stats_indicator.set_line_height(9);
    second_stats_indicator.set_name("Name");
    second_stats_indicator.set_kills("Kills");
    second_stats_indicator.set_deaths("Deaths");

    separator.set_width(1);
    separator.set_height(130);
    separator.set_background_color(60, 60, 60, 255);
    separator.set_draw_background(true);
}

void View::StatsRenderer::render(const Model::GameState& game_state) {
    clear();
    add_victories(game_state);

    first_team_stats.add_child(&first_stats_indicator);
    second_team_stats.add_child(&second_stats_indicator);

    for (const auto& player: game_state.players) {
        std::list<View::StatLine>* lines = nullptr;
        if (player.second->get_team() == Model::TeamID::CT)
            lines = &first_team_stats_items;
        else if (player.second->get_team() == Model::TeamID::TT)
            lines = &second_team_stats_items;
        if (!lines)
            continue;
        lines->emplace_back(controller);
        auto* last = &lines->back();
        last->set_name(player.second->get_name());
        last->set_kills(std::to_string(player.second->get_kills()));
        last->set_deaths(std::to_string(player.second->get_deaths()));
        last->set_background_color(78, 107, 60, 255);
        last->set_draw_background(true);
    }
    for (auto& line: first_team_stats_items) {
        first_team_stats.add_child(&line);
    }
    for (auto& line: second_team_stats_items) {
        second_team_stats.add_child(&line);
    }
}
