#ifndef CLIENT_GAME_CONTEXT_PICK_SPRITE_CONTEXT_H
#define CLIENT_GAME_CONTEXT_PICK_SPRITE_CONTEXT_H

#include "common/definitions.h"
#include "common/texture_id.h"

#include "base_context.h"

#include "entity/entity_positioner.h"
#include "entity/pane.h"
#include "entity/button.h"

namespace Controller {
class GameController;
};

namespace Context {
class PickSpriteContext: public BaseContext {
protected:
    SDL_Event placeholder;
    View::EntityPositioner positioner;

    View::Pane background;
    View::Button pick_sprite_1_button;
    View::Button pick_sprite_2_button;
    View::Button pick_sprite_3_button;
    View::Button pick_sprite_4_button;

    void build_button(View::Button& button, Model::TextureID texture_id);

    void render() override;
    void dispatch_events() override;

public:
    PickSpriteContext(Weak<Controller::GameController> controller);

    ~PickSpriteContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_PICK_SPRITE_CONTEXT_H
