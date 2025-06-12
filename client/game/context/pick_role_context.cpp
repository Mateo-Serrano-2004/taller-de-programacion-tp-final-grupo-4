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
    button.set_apply_scalation(true);
    button.set_keep_aspect_ratio(true);
    button.set_min_size(SDL2pp::Point(96, 96));
    button.set_max_size(SDL2pp::Point(160, 160));

    auto composite_command = make_unique<Command::CompositeCommand>(controller);
    composite_command->add_command(make_unique<Command::PickRoleCommand>(
        enum_translator.get_role_from_texture(texture_id)
    ));
    composite_command->add_command(make_unique<Command::SwitchContextCommand>("in-game"));

    button.set_command(std::move(composite_command));
}

void Context::PickRoleContext::update_size() {
    vertical_pane.set_max_size(renderer->GetViewport().GetSize());
    vertical_pane.set_size(renderer->GetViewport().GetSize());
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

    background.set_apply_scalation(true);
    background.set_keep_aspect_ratio(true);
    background.set_max_size(SDL2pp::Point(655, 160));
    background.set_min_size(SDL2pp::Point(399, 96));
    background.set_min_bounds(SDL2pp::Point(640, 480));

    build_button(pick_role_1_button, Model::TextureID::SPRITE_CT1);
    build_button(pick_role_2_button, Model::TextureID::SPRITE_CT2);
    build_button(pick_role_3_button, Model::TextureID::SPRITE_CT3);
    build_button(pick_role_4_button, Model::TextureID::SPRITE_CT4);
}

void Context::PickRoleContext::handle_event(Shared<Model::Event> event) {
    Model::EventType event_type = event->get_type();
    if (
        event_type == Model::EventType::SWITCH_CONTEXT || 
        event_type == Model::EventType::WINDOW_RESIZE 
    ) {
        update_size();
    }
} 
