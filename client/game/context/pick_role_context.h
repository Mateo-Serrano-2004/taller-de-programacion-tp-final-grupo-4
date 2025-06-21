#ifndef CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H
#define CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H

#include <cstdint>

#include "asset/texture_id.h"
#include "common/definitions.h"
#include "common/team.h"
#include "entity/button.h"
#include "entity/horizontal_pane.h"
#include "entity/label.h"
#include "entity/vertical_pane.h"
#include "event/event.h"
#include "handler/pick_role_event_handler_strategy.h"

#include "base_context.h"

namespace Controller {
class GameController;
};

namespace Context {
class PickRoleContext: public BaseContext {
    friend class Controller::PickRoleEventHandlerStrategy;

private:
    void trigger_buttons(Shared<SDL_Event> event);

protected:
    Model::TeamID current_team;
    Controller::PickRoleEventHandlerStrategy strategy;
    View::VerticalPane vertical_pane;
    View::Label label;
    View::HorizontalPane background;
    View::Button pick_role_1_button;
    View::Button pick_role_2_button;
    View::Button pick_role_3_button;
    View::Button pick_role_4_button;

    void build_button(View::Button& button);
    void set_role_for_button(View::Button& button, Model::TextureID role_texture_id);
    void set_buttons_for_ct();
    void set_buttons_for_tt();

    void render(uint8_t) override;
    void dispatch_events() override;

public:
    explicit PickRoleContext(Weak<Controller::GameController> controller);

    void update_team(Model::TeamID new_team);

    ~PickRoleContext() override = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H
