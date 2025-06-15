#include "pick_role_context.h"

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "common/event_type.h"

#include "controller/game_controller.h"
#include "controller/base_controller.h"

#include "command/composite_command.h"
#include "command/pick_role_command.h"
#include "command/switch_context_command.h"

#include "asset/texture_id.h"

#include "utils/enum_translator.h"

void Context::PickRoleContext::trigger_buttons(Shared<SDL_Event> event) {
    if (pick_role_1_button.trigger(event)) ;
    else if (pick_role_2_button.trigger(event)) ;
    else if (pick_role_3_button.trigger(event)) ;
    else if (pick_role_4_button.trigger(event)) ;
}

void Context::PickRoleContext::build_button(View::Button& button, Model::TextureID texture_id) {
    background.add_child(&button);
    button.set_draw_texture(true);
    button.set_texture(texture_id);
    button.set_texture_slice(SDL2pp::Rect(0, 0, 32, 32));
    button.set_size(SDL2pp::Point(96, 96));

    auto composite_command = make_unique<Command::CompositeCommand>(controller);
    composite_command->add_command(make_unique<Command::PickRoleCommand>(
        Model::EnumTranslator::get_role_from_texture(texture_id)
    ));
    composite_command->add_command(make_unique<Command::SwitchContextCommand>("in-game"));

    button.set_command(std::move(composite_command));
}

void Context::PickRoleContext::render() {
    vertical_pane.render();
}

void Context::PickRoleContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        strategy.handle(make_shared<SDL_Event>(placeholder));
    }
}

Context::PickRoleContext::PickRoleContext(Weak<Controller::GameController> controller)
: Context::BaseContext("pick-role", controller),
  strategy(controller, this),
  vertical_pane(controller, 10),
  label(controller),
  background(controller, 5),
  pick_role_1_button(controller),
  pick_role_2_button(controller),
  pick_role_3_button(controller),
  pick_role_4_button(controller) {

    vertical_pane.add_child(&label);
    vertical_pane.add_child(&background);
    vertical_pane.set_background_color(31, 45, 31, 255);
    vertical_pane.set_draw_background(true);

    label.set_text("Choose your skin");

    background.set_size(SDL2pp::Point(300, 200));

    build_button(pick_role_1_button, Model::TextureID::SPRITE_CT1);
    build_button(pick_role_2_button, Model::TextureID::SPRITE_CT2);
    build_button(pick_role_3_button, Model::TextureID::SPRITE_CT3);
    build_button(pick_role_4_button, Model::TextureID::SPRITE_CT4);
}
