#include "stat_line.h"

#include "controller/game_controller.h"

View::StatLine::StatLine(Weak<Controller::GameController> controller):
        View::VerticalPane(controller),
        line(controller),
        player_name_pane(controller),
        player_name(controller),
        kills_pane(controller),
        kills(controller),
        deaths_pane(controller),
        deaths(controller),
        separator(controller) {
    set_height(20);
    set_width(200);
    add_child(&line);
    add_child(&separator);

    line.add_child(&player_name_pane);
    line.add_child(&kills_pane);
    line.add_child(&deaths_pane);
    line.set_fit_to_children(true);

    player_name_pane.add_child(&player_name);
    player_name_pane.set_horizontal_alignment(0.1f);
    player_name_pane.set_width(150);
    player_name.set_width(25);
    player_name.set_height(19);
    player_name.set_font_size(12);

    kills_pane.set_width(25);
    kills_pane.set_height(19);
    kills_pane.add_child(&kills);
    kills.set_font_size(12);

    deaths_pane.set_width(25);
    deaths_pane.set_height(19);
    deaths_pane.add_child(&deaths);
    deaths.set_font_size(12);

    separator.set_width(200);
    separator.set_height(1);
    separator.set_background_color(60, 60, 60, 255);
    separator.set_draw_background(true);
}

void View::StatLine::set_name(const std::string& name) { player_name.set_text(name); }

void View::StatLine::set_kills(const std::string& kills_text) { kills.set_text(kills_text); }

void View::StatLine::set_deaths(const std::string& deaths_text) { deaths.set_text(deaths_text); }

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
    player_name.set_height(19);
    kills.set_width(25);
    kills.set_height(19);
    deaths.set_width(25);
    deaths.set_height(19);
}

void View::StatLine::set_line_height(uint8_t size) { line.set_height(size); }
