#include "quit_command.h"

#include <memory>

#include "controller/base_controller.h"

#include "event/quit_event.h"

Command::QuitCommand::QuitCommand(
    Weak<Controller::BaseController> controller
): Command::BaseCommand(controller) {}

void Command::QuitCommand::execute() {
    if (auto controller_locked = controller.lock()) {
        auto quit_event = make_shared<Model::QuitEvent>();
        controller_locked->handle_event(std::move(quit_event));
    }
}
