#include "stats_context.h"

#include <string>

#include "controller/game_controller.h"
#include "handler/game_state_manager.h"
#include "model/game_state.h"

void Context::StatsContext::update_board(const Model::GameState& game_state) {
    int ft_victories = game_state.first_team_victories;
    int st_victories = game_state.second_team_victories;

    ft_victories_label.set_text(std::to_string(ft_victories) + " victories");
    st_victories_label.set_text(std::to_string(st_victories) + " victories");
}

void Context::StatsContext::render(uint8_t frames) {
    auto game_state = game_state_manager->get_game_state();
    player_renderer.render(game_state, frames);
    hud_renderer.render(game_state, frames);

    update_board(game_state);

    viewport.render();
}

void Context::StatsContext::dispatch_events() {
    strategy.dispatch();
    strategy.handle_current_game_state();
}

Context::StatsContext::StatsContext(Weak<Controller::GameController> controller)
: Context::BaseContext("stats", controller),
  player_renderer(controller),
  hud_renderer(controller),
  strategy(controller),
  game_state_manager(controller.lock()->get_game_state_manager()),
  viewport(controller),
  board(controller),
  counter_line(controller),
  ft_victories_label(controller),
  st_victories_label(controller) {
    viewport.add_child(&board);

    board.set_width(400);
    board.set_height(100);
    board.set_vertical_alignment(0.0f);
    board.add_child(&counter_line);
    board.set_background_color(10, 30, 20, 255);
    board.set_draw_background(true);

    ft_victories_label.set_font_size(15);
    st_victories_label.set_font_size(15);
    counter_line.first_item.add_child(&ft_victories_label);
    counter_line.second_item.add_child(&st_victories_label);
}
