#include "shop_context.h"

#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>

#include "common/event_type.h"

#include "controller/game_controller.h"

#include "command/buy_weapon_command.h"

void Context::ShopContext::build_button(View::Button& button, const std::string& weapon_name, Model::WeaponID weapon_id) {
    background.add_child(&button);
    button.set_background_color(78, 107, 60, 255);
    button.set_draw_background(true);
    button.set_apply_scalation(true);
    button.set_font_size(16);
    button.set_text(weapon_name);
    button.set_min_size(button.get_size());
    button.set_size(button.get_size());
    button.set_max_height(button.get_height() + 64);
    button.set_max_width(button.get_width() + 64);

    button.set_command(
        std::move(make_unique<Command::BuyWeaponCommand>(weapon_id))
    );
}

void Context::ShopContext::trigger_buttons(Shared<SDL_Event> event) {
    buy_ak47.trigger(event);
    buy_m3.trigger(event);
    buy_awp.trigger(event);
}

void Context::ShopContext::update_size() {
    background.set_max_size(renderer->GetViewport().GetSize());
    background.set_size(renderer->GetViewport().GetSize());
}

void Context::ShopContext::render() {
    background.render();
}

void Context::ShopContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        strategy.handle(make_shared<SDL_Event>(placeholder));
    }
}

Context::ShopContext::ShopContext(Weak<Controller::GameController> controller)
: Context::BaseContext("shop", controller),
  strategy(controller, this),
  background(controller, 5),
  label(controller),
  buy_ak47(controller),
  buy_m3(controller),
  buy_awp(controller) {
    background.set_background_color(50, 100, 50, 255);
    background.set_draw_background(true);
    background.add_child(&label);

    label.set_font_size(16);
    label.set_text("Choose a weapon to buy");
    label.set_min_height(label.get_height());
    label.set_min_width(label.get_width());

    build_button(buy_ak47, "AK47", Model::WeaponID::AK47);
    build_button(buy_m3, "M3", Model::WeaponID::M3);
    build_button(buy_awp, "AWP", Model::WeaponID::AWP);
}

void Context::ShopContext::handle_event(Shared<Model::Event> event) {
    Model::EventType event_type = event->get_type();
    if (
        event_type == Model::EventType::SWITCH_CONTEXT || 
        event_type == Model::EventType::WINDOW_RESIZE 
    ) {
        update_size();
    }
}
