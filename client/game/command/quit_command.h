#ifndef CLIENT_GAME_COMMAND_QUIT_COMMAND_H
#define CLIENT_GAME_COMMAND_QUIT_COMMAND_H

#include "common/definitions.h"

#include "base_command.h"

namespace Controller {
class BaseController;
};

namespace Command {
class QuitCommand: public BaseCommand {
public:
    explicit QuitCommand(Weak<Controller::BaseController> controller = {});

    virtual void execute() override;

    virtual ~QuitCommand() override = default;
};
};  // namespace Command

#endif  // CLIENT_GAME_COMMAND_QUIT_COMMAND_H
