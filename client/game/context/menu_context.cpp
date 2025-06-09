#include "menu_context.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Rect.hh>

#include "controller/game_controller.h"
#include "controller/base_controller.h"

#include "command/quit_command.h"

#include "event/quit_event.h"

#include "asset/texture_id.h"

#include "exception/closed_window.h"

void Context::MenuContext::render() {
    player_renderer.render();

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
exit_button(controller) {
    background.set_background_color(31, 45, 31, 255);
    exit_button.set_background_color(78, 107, 60, 255);
    exit_button.set_text("Exit");

    exit_button.set_command(make_unique<Command::QuitCommand>());
}
