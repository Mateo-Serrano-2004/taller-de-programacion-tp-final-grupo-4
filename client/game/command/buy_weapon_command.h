#ifndef CLIENT_GAME_COMMAND_BUY_WEAPON_COMMAND_H
#define CLIENT_GAME_COMMAND_BUY_WEAPON_COMMAND_H

#include "common/definitions.h"
#include "common/weapon_id.h"

#include "base_command.h"

namespace Controller {
class BaseController;
};

namespace Command {
class BuyWeaponCommand: public BaseCommand {
protected:
    Model::WeaponID weapon_id;

public:
    explicit BuyWeaponCommand(Model::WeaponID weapon_id,
                              Weak<Controller::BaseController> controller = {});

    virtual void execute() override;

    virtual ~BuyWeaponCommand() override = default;
};
};  // namespace Command

#endif  // CLIENT_GAME_COMMAND_BUY_WEAPON_COMMAND_H
