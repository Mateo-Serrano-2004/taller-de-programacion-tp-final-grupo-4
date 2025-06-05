#ifndef CLIENT_GAME_ENTITY_BUTTON_H
#define CLIENT_GAME_ENTITY_BUTTON_H

#include <SDL2/SDL.h>

#include "common/definitions.h"
#include "common/texture_id.h"

#include "pane.h"

#include "handler/callback.h"

namespace Controller {
class BaseController;
};

namespace View {
class Button: public Pane {
protected:
    Controller::Callback callback;

public:
    Button(
        Model::TextureID texture_id,
        Weak<Controller::BaseController> controller,
        Pane* parent
    );

    Button(
        Model::TextureID texture_id,
        Weak<Controller::BaseController> controller
    );

    bool check_click(Shared<SDL_Event> event) const;
    void on_click(std::function<void(Weak<Controller::BaseController>)> callback);
    bool trigger(Shared<SDL_Event> event);

    virtual ~Button() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_BUTTON_H
