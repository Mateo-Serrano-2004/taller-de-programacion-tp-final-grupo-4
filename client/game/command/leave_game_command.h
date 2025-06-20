#ifndef CLIENT_GAME_COMMAND_LEAVE_GAME_COMMAND_H
#define CLIENT_GAME_COMMAND_LEAVE_GAME_COMMAND_H

#include "common/definitions.h"

#include "base_command.h"

namespace Controller {
class BaseController;
};

namespace Command {
class LeaveGameCommand: public BaseCommand {
public:
    explicit LeaveGameCommand(Weak<Controller::BaseController> controller = {});

    virtual void execute() override;

    virtual ~LeaveGameCommand() override = default;
};
};  // namespace Command

#endif  // CLIENT_GAME_COMMAND_LEAVE_GAME_COMMAND_H
