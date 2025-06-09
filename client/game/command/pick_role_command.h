#ifndef CLIENT_GAME_COMMAND_PICK_ROLE_COMMAND_H
#define CLIENT_GAME_COMMAND_PICK_ROLE_COMMAND_H

#include "common/definitions.h"
#include "common/role_id.h"

#include "base_command.h"

namespace Controller {
class BaseController;
};

namespace Command {
class PickRoleCommand: public BaseCommand {
protected:
    Model::RoleID role_id;

public:
    PickRoleCommand(
        Model::RoleID role_id,
        Weak<Controller::BaseController> controller = {}
    );

    virtual void execute() override;

    virtual ~PickRoleCommand() override = default;
};
};

#endif // CLIENT_GAME_COMMAND_PICK_ROLE_COMMAND_H
