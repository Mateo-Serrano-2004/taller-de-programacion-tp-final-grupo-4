#include "pick_sprite_command.h"

#include <memory>

#include "controller/base_controller.h"

#include "event/pick_sprite_event.h"

Command::PickSpriteCommand::PickSpriteCommand(
    Model::TextureID sprite_id,
    Weak<Controller::BaseController> controller
): Command::BaseCommand(controller), sprite_id(sprite_id) {}

void Command::PickSpriteCommand::execute() {
    if (auto controller_locked = controller.lock()) {
        auto pick_sprite_event = make_shared<Model::PickSpriteEvent>(sprite_id);
        controller_locked->handle_event(std::move(pick_sprite_event));
    }
}
