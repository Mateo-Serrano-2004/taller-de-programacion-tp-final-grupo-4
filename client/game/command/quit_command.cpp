#include "quit_command.h"

#include <memory>

#include "controller/base_controller.h"
#include "event/quit_event.h"

Command::QuitCommand::QuitCommand(Weak<Controller::BaseController> controller):
        Command::BaseCommand(controller) {}

void Command::QuitCommand::execute() {
    if (auto controller_locked = controller.lock()) {
        controller_locked->push_event(make_shared<Model::QuitEvent>());
    }
}
