#ifndef CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H
#define CLIENT_GAME_CONTEXT_PICK_ROLE_CONTEXT_H

#include "common/definitions.h"
#include "common/texture_id.h"

#include "base_context.h"

#include "entity/entity_positioner.h"
#include "entity/pane.h"
#include "entity/button.h"

#include "enum/enum_translator.h"

namespace Controller {
class GameController;
};

namespace Context {
class PickRoleContext: public BaseContext {
protected:
    SDL_Event placeholder;
    View::EntityPositioner positioner;
    Model::EnumTranslator enum_translator;

    View::Pane background;
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
