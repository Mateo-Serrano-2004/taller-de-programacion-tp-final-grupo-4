#include "leave_game_command.h"

#include <memory>

#include "controller/base_controller.h"
#include "event/leave_game_event.h"

Command::LeaveGameCommand::LeaveGameCommand(Weak<Controller::BaseController> controller):
        Command::BaseCommand(controller) {}

void Command::LeaveGameCommand::execute() {
    if (auto controller_locked = controller.lock()) {
        controller_locked->push_event(make_shared<Model::LeaveGameEvent>());
    }
}
