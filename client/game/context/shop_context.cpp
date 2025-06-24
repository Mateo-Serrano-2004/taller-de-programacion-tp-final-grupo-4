#include "shop_context.h"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>

#include "command/buy_weapon_command.h"
#include "command/composite_command.h"
#include "command/switch_context_command.h"
#include "common/event_type.h"
#include "controller/game_controller.h"

void Context::ShopContext::build_button(View::Button& button, const std::string& weapon_name,
                                        Model::WeaponID weapon_id) {
    background.add_child(&button);
    button.set_background_color(78, 107, 60, 255);
    button.set_draw_background(true);
    button.set_font_size(16);
    button.set_text(weapon_name);
    button.set_padding(6);

    auto composite = make_unique<Command::CompositeCommand>(controller);
    composite->add_command(make_unique<Command::BuyWeaponCommand>(weapon_id));
    composite->add_command(make_unique<Command::SwitchContextCommand>("in-game"));
    button.set_command(std::move(composite));
}

void Context::ShopContext::trigger_buttons(Shared<SDL_Event> event) {
    buy_ak47.trigger(event);
    buy_m3.trigger(event);
    buy_awp.trigger(event);
}

void Context::ShopContext::render(uint8_t) { background.render(); }

void Context::ShopContext::dispatch_events() { strategy.dispatch(); }

Context::ShopContext::ShopContext(Weak<Controller::GameController> controller):
        Context::BaseContext("shop", controller),
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

    build_button(buy_ak47, "AK47", Model::WeaponID::AK47);
    build_button(buy_m3, "M3", Model::WeaponID::M3);
    build_button(buy_awp, "AWP", Model::WeaponID::AWP);
}
