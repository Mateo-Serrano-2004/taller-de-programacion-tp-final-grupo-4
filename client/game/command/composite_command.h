#ifndef CLIENT_GAME_COMMAND_COMPOSITE_COMMAND_H
#define CLIENT_GAME_COMMAND_COMPOSITE_COMMAND_H

#include <list>

#include "common/definitions.h"

#include "base_command.h"

namespace Controller {
class BaseController;
};

namespace Command {
class CompositeCommand: public BaseCommand {
protected:
    std::list<Unique<BaseCommand>> commands;

public:
    explicit CompositeCommand(Weak<Controller::BaseController> controller);

    void add_command(Unique<BaseCommand> new_command);

    virtual void execute() override;

    virtual ~CompositeCommand() override = default;
};
};  // namespace Command

#endif  // CLIENT_GAME_COMMAND_COMPOSITE_COMMAND_H
