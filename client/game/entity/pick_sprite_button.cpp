#include "pick_sprite_button.h"

#include <utility>

#include "pane.h"

#include "controller/game_controller.h"

#include "event/pick_sprite_event.h"
#include "event/switch_context_event.h"

View::PickSpriteButton::PickSpriteButton(
    Model::TextureID sprite_id,
    Weak<Controller::GameController> controller,
    Pane* parent
): View::Button(sprite_id, controller, parent) {
    on_click(
        [sprite_id] (Weak<Controller::BaseController> base_controller) {
            auto pick_sprite_event = make_shared<Model::PickSpriteEvent>(sprite_id);
            auto switch_context_event = make_shared<Model::SwitchContextEvent>("in-game");
            base_controller.lock()->handle_event(std::move(pick_sprite_event));
            base_controller.lock()->handle_event(std::move(switch_context_event));
        }
    );
}

View::PickSpriteButton::PickSpriteButton(
    Model::TextureID sprite_id,
    Weak<Controller::GameController> controller
): View::PickSpriteButton(sprite_id, controller, nullptr) {}

Model::TextureID View::PickSpriteButton::get_sprite_id() const {
    return sprite_id;
}

void View::PickSpriteButton::set_sprite_id(Model::TextureID new_sprite_id) {
    sprite_id = new_sprite_id;
}
