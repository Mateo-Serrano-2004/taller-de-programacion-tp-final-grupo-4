#ifndef CLIENT_GAME_ENTITY_BUTTON_H
#define CLIENT_GAME_ENTITY_BUTTON_H

#include "common/definitions.h"

#include "pane.h"

namespace Controller {
class BaseController;
};

namespace View {
class Button: public Pane {
public:
    Button(
        short_id_t texture_id,
        Weak<Controller::BaseController> controller,
        Pane* parent
    );

    Button(
        short_id_t texture_id,
        Weak<Controller::BaseController> controller
    );

    ~Button() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_BUTTON_H
