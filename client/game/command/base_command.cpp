#include "base_command.h"

#include "controller/base_controller.h"

Command::BaseCommand::BaseCommand(Weak<Controller::BaseController> controller):
        controller(controller) {}

void Command::BaseCommand::set_controller(Weak<Controller::BaseController> new_controller) {
    controller = new_controller;
}

bool Command::BaseCommand::is_executable() { return (bool)controller.lock(); }
