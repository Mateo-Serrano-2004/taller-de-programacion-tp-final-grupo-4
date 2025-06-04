#ifndef CLIENT_GAME_ENTITY_BACKGROUND_H
#define CLIENT_GAME_ENTITY_BACKGROUND_H

#include "common/definitions.h"

#include "pane.h"

namespace Controller {
class BaseController;
};

namespace View {
class Background: public Pane {
public:
    Background(
        short_id_t texture_id,
        Weak<Controller::BaseController> controller,
        Pane* parent
    );

    Background(
        short_id_t texture_id,
        Weak<Controller::BaseController> controller
    );

    ~Background() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_BACKGROUND_H