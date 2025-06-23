#include "stat_line.h"

#include "controller/game_controller.h"

View::StatLine::StatLine(Weak<Controller::GameController> controller)
: View::VerticalPane(controller),
  line(controller),
  player_name(controller),
  kills_pane(controller),
  kills(controller),
  deaths_pane(controller),
  deaths(controller),
  separator(controller) {
    add_child(&line);
    set_fit_to_children(true);

    line.add_child(&player_name);
    line.add_child(&deaths_pane);
    line.add_child(&separator);
    line.set_width(150);
    line.set_height(19);

    player_name.set_width(100);
    player_name.set_height(19);

    kills_pane.set_width(25);
    kills_pane.set_height(19);
    kills_pane.add_child(&kills);
    kills.set_font_size(15);

    deaths_pane.set_width(25);
    deaths_pane.set_height(19);
    deaths_pane.add_child(&deaths);
    deaths.set_font_size(15);

    separator.set_width(190);
    separator.set_height(1);
    separator.set_background_color(60, 60, 60, 255);
    separator.set_draw_background(true);
}

void View::StatLine::set_name(const std::string& name) {
    player_name.set_text(name);
}

void View::StatLine::set_kills(const std::string& kills_text) {
    kills.set_text(kills_text);
}

void View::StatLine::set_deaths(const std::string& deaths_text) {
    deaths.set_text(deaths_text);
}

void View::StatLine::set_all_texts_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    player_name.set_font_color(red, green, blue, alpha);
    kills.set_font_color(red, green, blue, alpha);
    deaths.set_font_color(red, green, blue, alpha);
}

void View::StatLine::set_all_fonts_size(uint8_t size) {
    player_name.set_font_size(size);
    kills.set_font_size(size);
    deaths.set_font_size(size);

    player_name.set_width(100);
    player_name.set_height(20);
    kills.set_width(25);
    kills.set_height(20);
    deaths.set_width(25);
    deaths.set_height(20);
}
