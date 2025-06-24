#include "pick_role_context.h"

#include <cstdint>
#include <memory>
#include <utility>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "asset/texture_id.h"
#include "command/composite_command.h"
#include "command/pick_role_command.h"
#include "command/switch_context_command.h"
#include "common/event_type.h"
#include "common/team.h"
#include "controller/base_controller.h"
#include "controller/game_controller.h"
#include "utils/enum_translator.h"

void Context::PickRoleContext::trigger_buttons(Shared<SDL_Event> event) {
    if (current_team == Model::TeamID::NONE)
        return;
    if (pick_role_1_button.trigger(event)) {
    } else if (pick_role_2_button.trigger(event)) {
    } else if (pick_role_3_button.trigger(event)) {
    } else if (pick_role_4_button.trigger(event)) {
    }
}

void Context::PickRoleContext::build_button(View::Button& button) {
    background.add_child(&button);
    button.set_draw_texture(true);
    button.set_texture_slice(SDL2pp::Rect(0, 0, 32, 32));
    button.set_size(SDL2pp::Point(96, 96));
}

void Context::PickRoleContext::set_role_for_button(View::Button& button,
                                                   Model::TextureID role_texture_id) {
    button.clear_command();

    button.set_texture(role_texture_id);

    auto composite_command = make_unique<Command::CompositeCommand>(controller);
    composite_command->add_command(make_unique<Command::PickRoleCommand>(
            Model::EnumTranslator::get_role_from_texture(role_texture_id)));
    composite_command->add_command(make_unique<Command::SwitchContextCommand>("in-game"));

    button.set_command(std::move(composite_command));
}

void Context::PickRoleContext::set_buttons_for_ct() {
    set_role_for_button(pick_role_1_button, Model::TextureID::SPRITE_CT1);
    set_role_for_button(pick_role_2_button, Model::TextureID::SPRITE_CT2);
    set_role_for_button(pick_role_3_button, Model::TextureID::SPRITE_CT3);
    set_role_for_button(pick_role_4_button, Model::TextureID::SPRITE_CT4);
}

void Context::PickRoleContext::set_buttons_for_tt() {
    set_role_for_button(pick_role_1_button, Model::TextureID::SPRITE_T1);
    set_role_for_button(pick_role_2_button, Model::TextureID::SPRITE_T2);
    set_role_for_button(pick_role_3_button, Model::TextureID::SPRITE_T3);
    set_role_for_button(pick_role_4_button, Model::TextureID::SPRITE_T4);
}

void Context::PickRoleContext::render(uint8_t) {
    if (current_team != Model::TeamID::NONE)
        vertical_pane.render();
}

void Context::PickRoleContext::dispatch_events() { strategy.dispatch(); }

Context::PickRoleContext::PickRoleContext(Weak<Controller::GameController> controller):
        Context::BaseContext("pick-role", controller),
        current_team(Model::TeamID::NONE),
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

    build_button(pick_role_1_button);
    build_button(pick_role_2_button);
    build_button(pick_role_3_button);
    build_button(pick_role_4_button);
}

void Context::PickRoleContext::update_team(Model::TeamID new_team) {
    current_team = new_team;
    if (new_team == Model::TeamID::TT) {
        set_buttons_for_tt();
    } else {
        set_buttons_for_ct();
    }
}
