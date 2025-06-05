#ifndef CLIENT_GAME_CONTEXT_PICK_SPRITE_CONTEXT_H
#define CLIENT_GAME_CONTEXT_PICK_SPRITE_CONTEXT_H

#include "common/definitions.h"

#include "base_context.h"

#include "entity/entity_positioner.h"
#include "entity/pane.h"
#include "entity/pick_sprite_button.h"

namespace Controller {
class GameController;
};

namespace Context {
class PickSpriteContext: public BaseContext {
protected:
    SDL_Event placeholder;
    View::EntityPositioner positioner;

    View::Pane background;
    View::PickSpriteButton pick_sprite_1_button;
    View::PickSpriteButton pick_sprite_2_button;
    View::PickSpriteButton pick_sprite_3_button;
    View::PickSpriteButton pick_sprite_4_button;

    void render() override;
    void dispatch_events() override;

public:
    PickSpriteContext(Weak<Controller::GameController> controller);

    ~PickSpriteContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_PICK_SPRITE_CONTEXT_H
