#ifndef CLIENT_GAME_COMMAND_SWITCH_CONTEXT_COMMAND_H
#define CLIENT_GAME_COMMAND_SWITCH_CONTEXT_COMMAND_H

#include <string>

#include "common/definitions.h"

#include "base_command.h"

namespace Controller {
class BaseController;
};

namespace Command {
class SwitchContextCommand: public BaseCommand {
protected:
    std::string new_context_name;

public:
    explicit SwitchContextCommand(const std::string& new_context_name,
                                  Weak<Controller::BaseController> controller = {});

    virtual void execute() override;

    virtual ~SwitchContextCommand() override = default;
};
};  // namespace Command

#endif  // CLIENT_GAME_COMMAND_SWITCH_CONTEXT_COMMAND_H
