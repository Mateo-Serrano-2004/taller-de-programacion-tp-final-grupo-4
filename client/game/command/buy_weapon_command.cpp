#include "buy_weapon_command.h"

#include <memory>
#include <utility>

#include "controller/base_controller.h"
#include "event/buy_weapon_event.h"

Command::BuyWeaponCommand::BuyWeaponCommand(Model::WeaponID weapon_id,
                                            Weak<Controller::BaseController> controller):
        Command::BaseCommand(controller), weapon_id(weapon_id) {}

void Command::BuyWeaponCommand::execute() {
    if (auto controller_locked = controller.lock()) {
        auto buy_weapon_event = make_shared<Model::BuyWeaponEvent>(weapon_id);
        controller_locked->push_event(std::move(buy_weapon_event));
    }
}
