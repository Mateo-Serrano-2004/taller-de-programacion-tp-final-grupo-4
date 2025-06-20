#ifndef CLIENT_GAME_ANIMATION_WINNER_TEAM_MESSAGE_ANIMATION_H
#define CLIENT_GAME_ANIMATION_WINNER_TEAM_MESSAGE_ANIMATION_H

#include <string>

#include <SDL2pp/Color.hh>

#include "asset/animation_id.h"
#include "common/definitions.h"
#include "common/team.h"
#include "entity/label.h"
#include "entity/vertical_pane.h"

#include "framed_animation.h"

namespace Controller {
class GameController;
};

namespace View {
class WinnerTeamMessageAnimation: public FramedAnimation {
private:
    VerticalPane viewport;
    Label message;

    std::string get_message(Model::TeamID winner_team);
    SDL2pp::Color get_color(Model::TeamID winner_team);

public:
    WinnerTeamMessageAnimation(Weak<Controller::GameController> controller,
                               Model::TeamID winner_team);

    void render() override;

    ~WinnerTeamMessageAnimation() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ANIMATION_WINNER_TEAM_MESSAGE_ANIMATION_H
