#ifndef CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H
#define CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "base_context.h"

#include "handler/pick_role_event_handler_strategy.h"

#include "asset/texture_id.h"

#include "event/event.h"

#include "entity/horizontal_pane.h"
#include "entity/vertical_pane.h"
#include "entity/label.h"
#include "entity/button.h"

#include "enum/enum_translator.h"

namespace Controller {
class GameController;
};

namespace Context {
class PickRoleContext: public BaseContext {
friend class Controller::PickRoleEventHandlerStrategy;

private:
    void trigger_buttons(Shared<SDL_Event> event);

protected:
    SDL_Event placeholder;
    Model::EnumTranslator enum_translator;
    Controller::PickRoleEventHandlerStrategy strategy;
    View::VerticalPane vertical_pane;
    View::Label label;
    View::HorizontalPane background;
    View::Button pick_role_1_button;
    View::Button pick_role_2_button;
    View::Button pick_role_3_button;
    View::Button pick_role_4_button;

    void build_button(View::Button& button, Model::TextureID texture_id);

    void render() override;
    void dispatch_events() override;

public:
    PickRoleContext(Weak<Controller::GameController> controller);
    ~PickRoleContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H
