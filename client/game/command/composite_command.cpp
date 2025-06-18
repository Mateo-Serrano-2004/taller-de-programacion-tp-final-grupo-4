#include "composite_command.h"

#include <algorithm>
#include <utility>

#include "controller/base_controller.h"

Command::CompositeCommand::CompositeCommand(Weak<Controller::BaseController> controller):
        Command::BaseCommand(controller) {}

void Command::CompositeCommand::add_command(Unique<Command::BaseCommand> new_command) {
    if (!new_command->is_executable())
        new_command->set_controller(controller);
    commands.push_back(std::move(new_command));
}

void Command::CompositeCommand::execute() {
    std::for_each(commands.begin(), commands.end(), [](Unique<Command::BaseCommand>& command) {
        if (command->is_executable())
            command->execute();
    });
}
