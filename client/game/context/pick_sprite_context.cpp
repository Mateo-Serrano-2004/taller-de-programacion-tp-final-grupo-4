#include "pick_sprite_context.h"

#include <utility>

#include <SDL2/SDL.h>

#include "common/texture_id.h"

#include "controller/game_controller.h"
#include "controller/base_controller.h"

#include "event/quit_event.h"
#include "event/switch_context_event.h"
#include "event/pick_sprite_event.h"

Context::PickSpriteContext::PickSpriteContext(Weak<Controller::GameController> controller)
: Context::BaseContext("pick-sprite", controller),
  background(Model::TextureID::BG_DARK_GREEN, controller),
  pick_sprite_1_button(Model::TextureID::SPRITE_CT1, controller, &background),
  pick_sprite_2_button(Model::TextureID::SPRITE_CT2, controller, &background),
  pick_sprite_3_button(Model::TextureID::SPRITE_CT3, controller, &background),
  pick_sprite_4_button(Model::TextureID::SPRITE_CT4, controller, &background) {
    pick_sprite_1_button.set_texture_slice(
        SDL2pp::Rect(0, 0, 32, 32)
    );
    pick_sprite_2_button.set_texture_slice(
        SDL2pp::Rect(0, 0, 32, 32)
    );
    pick_sprite_3_button.set_texture_slice(
        SDL2pp::Rect(0, 0, 32, 32)
    );
    pick_sprite_4_button.set_texture_slice(
        SDL2pp::Rect(0, 0, 32, 32)
    );
}

void Context::PickSpriteContext::render() {
    background.render();

    positioner.size_pane_relatively_to_parent(pick_sprite_1_button, 0.2, 0.3);
    positioner.size_pane_relatively_to_parent(pick_sprite_2_button, 0.2, 0.3);
    positioner.size_pane_relatively_to_parent(pick_sprite_3_button, 0.2, 0.3);
    positioner.size_pane_relatively_to_parent(pick_sprite_4_button, 0.2, 0.3);

    positioner.place_pane_relatively_to_parent(pick_sprite_1_button, 0.1, 0.5);
    positioner.place_pane_relatively_to_parent(pick_sprite_2_button, 0.35, 0.5);
    positioner.place_pane_relatively_to_parent(pick_sprite_3_button, 0.65, 0.5);
    positioner.place_pane_relatively_to_parent(pick_sprite_4_button, 0.9, 0.5);

    pick_sprite_1_button.render();
    pick_sprite_2_button.render();
    pick_sprite_3_button.render();
    pick_sprite_4_button.render();
}

void Context::PickSpriteContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        auto event = make_shared<SDL_Event>(placeholder);

        if (placeholder.type == SDL_QUIT) {
            auto quit_event = make_shared<Model::QuitEvent>();
            controller.lock()->handle_event(std::move(quit_event));
        } else {
            pick_sprite_1_button.trigger(event);
            pick_sprite_2_button.trigger(event);
            pick_sprite_3_button.trigger(event);
            pick_sprite_4_button.trigger(event);
        }
    }
}
