#ifndef CLIENT_GAME_COMMAND_BASE_COMMAND_H
#define CLIENT_GAME_COMMAND_BASE_COMMAND_H

#include "common/definitions.h"

namespace Controller {
class BaseController;
};

namespace Command {
class BaseCommand {
protected:
    Weak<Controller::BaseController> controller;

public:
    explicit BaseCommand(Weak<Controller::BaseController> controller = {});

    void set_controller(Weak<Controller::BaseController> new_controller);

    bool is_executable();
    virtual void execute() = 0;

    virtual ~BaseCommand() = default;
};
};  // namespace Command

#endif  // CLIENT_GAME_COMMAND_BASE_COMMAND_H
