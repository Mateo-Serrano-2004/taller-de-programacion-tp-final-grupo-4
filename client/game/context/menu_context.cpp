#include "menu_context.h"

#include <cstdint>
#include <memory>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>

#include "command/leave_game_command.h"
#include "command/switch_context_command.h"
#include "common/event_type.h"
#include "controller/game_controller.h"
#include "handler/game_state_manager.h"
#include "model/game_state.h"

void Context::MenuContext::trigger_buttons(Shared<SDL_Event> event) {
    if (exit_button.trigger(event)) {
    } else if (return_game_button.trigger(event)) {
    }
}

void Context::MenuContext::render(uint8_t frames) {
    Model::GameState game_state = game_state_manager->get_game_state();
    player_renderer.render(game_state, frames);
    viewport.render();
}

void Context::MenuContext::dispatch_events() { strategy.dispatch(); }

void Context::MenuContext::build_button(View::Button& button) {
    button.set_background_color(78, 107, 60, 255);
    button.set_draw_background(true);
    button.set_font_size(16);
    button.set_padding(8);
}

Context::MenuContext::MenuContext(Weak<Controller::GameController> controller):
        Context::BaseContext("menu", controller),
        strategy(controller, this),
        player_renderer(controller),
        game_state_manager(controller.lock()->get_game_state_manager()),
        viewport(controller),
        background(controller),
        ask_to_leave_label(controller),
        buttons(controller),
        return_game_button(controller),
        exit_button(controller) {
    viewport.add_child(&background);

    background.add_child(&ask_to_leave_label);
    background.add_child(&buttons);

    buttons.add_child(&return_game_button);
    buttons.add_child(&exit_button);

    background.set_background_color(31, 45, 31, 255);
    background.set_draw_background(true);
    background.set_size(SDL2pp::Point(300, 200));
    background.set_gap_y(15);

    buttons.set_height(60);
    buttons.set_gap_x(5);

    ask_to_leave_label.set_text("Leave game?");
    ask_to_leave_label.set_font_size(16);
    ask_to_leave_label.set_padding(8);

    build_button(exit_button);
    build_button(return_game_button);

    exit_button.set_text("Exit");
    return_game_button.set_text("Return game");

    exit_button.set_command(make_unique<Command::LeaveGameCommand>());
    return_game_button.set_command(make_unique<Command::SwitchContextCommand>("in-game"));
}
