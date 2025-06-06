#ifndef CLIENT_GAME_COMMAND_PICK_SPRITE_COMMAND_H
#define CLIENT_GAME_COMMAND_PICK_SPRITE_COMMAND_H

#include "common/definitions.h"
#include "common/texture_id.h"

#include "base_command.h"

namespace Controller {
class BaseController;
};

namespace Command {
class PickSpriteCommand: public BaseCommand {
protected:
    Model::TextureID sprite_id;

public:
    PickSpriteCommand(
        Model::TextureID sprite_id,
        Weak<Controller::BaseController> controller = {}
    );

    virtual void execute() override;

    virtual ~PickSpriteCommand() override = default;
};
};

#endif // CLIENT_GAME_COMMAND_PICK_SPRITE_COMMAND_H
