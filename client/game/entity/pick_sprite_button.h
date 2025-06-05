#ifndef CLIENT_GAME_ENTITY_PICK_SPRITE_BUTTON_H
#define CLIENT_GAME_ENTITY_PICK_SPRITE_BUTTON_H

#include "common/definitions.h"
#include "common/texture_id.h"

#include "button.h"

namespace Controller {
class GameController;
};

namespace View {
class Pane;

class PickSpriteButton: public Button {
private:
    Model::TextureID sprite_id;

public:
    PickSpriteButton(
        Model::TextureID sprite_id,
        Weak<Controller::GameController> controller,
        Pane* parent
    );

    PickSpriteButton(
        Model::TextureID sprite_id,
        Weak<Controller::GameController> controller
    );

    Model::TextureID get_sprite_id() const;
    void set_sprite_id(Model::TextureID new_sprite_id);

    ~PickSpriteButton() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_PICK_SPRITE_BUTTON_H
