#include "pick_role_context.h"

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "controller/game_controller.h"
#include "controller/base_controller.h"

#include "command/composite_command.h"
#include "command/pick_role_command.h"
#include "command/switch_context_command.h"

#include "asset/texture_id.h"

#include "event/quit_event.h"
#include "event/switch_context_event.h"
#include "event/pick_role_event.h"

Context::PickRoleContext::PickRoleContext(Weak<Controller::GameController> controller)
: Context::BaseContext("pick-role", controller),
  background(controller, 5),
  pick_role_1_button(controller),
  pick_role_2_button(controller),
  pick_role_3_button(controller),
  pick_role_4_button(controller) {

    background.set_background_color(31, 45, 31, 255);

    build_button(pick_role_1_button, Model::TextureID::SPRITE_CT1);
    build_button(pick_role_2_button, Model::TextureID::SPRITE_CT2);
    build_button(pick_role_3_button, Model::TextureID::SPRITE_CT3);
    build_button(pick_role_4_button, Model::TextureID::SPRITE_CT4);
}

void Context::PickRoleContext::build_button(View::Button& button, Model::TextureID texture_id) {
    button.set_background_color(78, 107, 60, 255);
    button.set_texture(texture_id);
    button.set_draw_texture(true);
    button.set_texture_slice(SDL2pp::Rect(0, 0, 32, 32));
    button.set_size(SDL2pp::Point(128, 128));
    background.add_child(&button);

    auto composite_command = make_unique<Command::CompositeCommand>(controller);
    composite_command->add_command(make_unique<Command::PickRoleCommand>(
        enum_translator.get_role_from_texture(texture_id)
    ));
    composite_command->add_command(make_unique<Command::SwitchContextCommand>("in-game"));

    button.set_command(std::move(composite_command));
}

void Context::PickRoleContext::render() {
    background.render();
}

void Context::PickRoleContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        auto event = make_shared<SDL_Event>(placeholder);

        if (placeholder.type == SDL_QUIT) {
            auto quit_event = make_shared<Model::QuitEvent>();
            controller.lock()->handle_event(std::move(quit_event));
        } else {
            // Para evitar que se llamen todos, aunque es medio innecesario y feo
            if (pick_role_1_button.trigger(event)) ;
            else if (pick_role_2_button.trigger(event)) ;
            else if (pick_role_3_button.trigger(event)) ;
            else if (pick_role_4_button.trigger(event)) ;
        }
    }
}
