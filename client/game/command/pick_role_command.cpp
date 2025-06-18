#include "pick_role_command.h"

#include <memory>
#include <utility>

#include "controller/base_controller.h"
#include "event/pick_role_event.h"

Command::PickRoleCommand::PickRoleCommand(Model::RoleID role_id,
                                          Weak<Controller::BaseController> controller):
        Command::BaseCommand(controller), role_id(role_id) {}

void Command::PickRoleCommand::execute() {
    if (auto controller_locked = controller.lock()) {
        auto pick_role_event = make_shared<Model::PickRoleEvent>(role_id);
        controller_locked->push_event(std::move(pick_role_event));
    }
}
