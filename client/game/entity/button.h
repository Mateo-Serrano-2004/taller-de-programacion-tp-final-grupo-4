#ifndef CLIENT_GAME_ENTITY_BUTTON_H
#define CLIENT_GAME_ENTITY_BUTTON_H

#include <string>

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "command/base_command.h"

#include "asset/texture_id.h"

#include "label.h"

namespace Controller {
class BaseController;
};

namespace View {
class Button: public Label {
protected:
    Unique<Command::BaseCommand> command;
    Weak<Controller::BaseController> controller;

public:
    Button(Weak<Controller::BaseController> controller);

    bool check_click(Shared<SDL_Event> event) const;

    void set_command(Unique<Command::BaseCommand> new_command);
    void clear_command();

    bool trigger(Shared<SDL_Event> event);

    virtual ~Button() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_BUTTON_H
