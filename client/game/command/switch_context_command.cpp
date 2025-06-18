#include "switch_context_command.h"

#include <memory>
#include <utility>

#include "controller/base_controller.h"
#include "event/switch_context_event.h"

Command::SwitchContextCommand::SwitchContextCommand(const std::string& new_context_name,
                                                    Weak<Controller::BaseController> controller):
        Command::BaseCommand(controller), new_context_name(new_context_name) {}

void Command::SwitchContextCommand::execute() {
    if (auto controller_locked = controller.lock()) {
        auto switch_context_event = make_shared<Model::SwitchContextEvent>(new_context_name);
        controller_locked->push_event(std::move(switch_context_event));
    }
}
