#include "winner_team_message_animation.h"

#include <string>

#include "controller/game_controller.h"

std::string View::WinnerTeamMessageAnimation::get_message(Model::TeamID winner_team) {
    std::string team = winner_team == Model::TeamID::CT ? "Counter Terrorists" : "Terorists";
    return team + " win";
}

SDL2pp::Color View::WinnerTeamMessageAnimation::get_color(Model::TeamID winner_team) {
    return winner_team == Model::TeamID::CT ? SDL2pp::Color(0, 0, 255) : SDL2pp::Color(255, 0, 0);
}

View::WinnerTeamMessageAnimation::WinnerTeamMessageAnimation(
        Weak<Controller::GameController> controller, Model::TeamID team):
        View::FramedAnimation(controller), viewport(controller), message(controller) {
    viewport.add_child(&message);
    viewport.set_vertical_alignment(0.2f);
    message.set_text(get_message(team));
    message.set_font_size(15);
    auto color = get_color(team);
    message.set_font_color(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
    total_frames = 160;
}

void View::WinnerTeamMessageAnimation::render() { viewport.render(); }
