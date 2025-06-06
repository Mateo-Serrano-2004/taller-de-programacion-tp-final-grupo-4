#include "menu_context.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Color.hh>

#include "common/texture_id.h"

#include "controller/game_controller.h"
#include "controller/base_controller.h"

#include "asset/background_id.h"

#include "command/quit_command.h"

#include "event/quit_event.h"

#include "exception/closed_window.h"

void Context::MenuContext::render() {
    player_renderer.render();

    positioner.size_pane_relatively_to_parent(background, 0.6, 0.6);
    positioner.place_pane_relatively_to_parent(background, 0.5, 0.5);

    exit_button.set_position(SDL2pp::Rect(0, 0, 60, 40));

    positioner.place_pane_relatively_to_parent(exit_button, 0.5, 0.8);

    exit_button.set_texture_slice_to_match_position();

    background.render();
    exit_button.render();
}

void Context::MenuContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        auto event = make_shared<SDL_Event>(placeholder);

        if (!exit_button.trigger(event)) {
            event_handler_strategy.handle(event);
        }
    }
}

Context::MenuContext::MenuContext(Weak<Controller::GameController> controller):
Context::BaseContext("menu", controller),
event_handler_strategy(controller),
player_renderer(controller),
background(controller),
exit_button(controller, &background) {
    background.set_background(Model::BackgroundID::BG_DARK_GREEN);
    exit_button.set_background(Model::BackgroundID::BG_SMOOTH_GREEN);

    exit_button.set_command(make_unique<Command::QuitCommand>());
}
