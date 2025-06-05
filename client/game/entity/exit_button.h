#ifndef CLIENT_GAME_ENTITY_EXIT_BUTTON_H
#define CLIENT_GAME_ENTITY_EXIT_BUTTON_H

#include <functional>

#include "common/definitions.h"
#include "common/texture_id.h"

#include "button.h"

namespace Controller {
class BaseController;
};

namespace View {
class ExitButton: public Button {
public:
    ExitButton(
        Model::TextureID texture_id,
        Weak<Controller::BaseController> controller,
        Pane* parent
    );

    ExitButton(
        Model::TextureID texture_id,
        Weak<Controller::BaseController> controller
    );

    ~ExitButton() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_EXIT_BUTTON_H
