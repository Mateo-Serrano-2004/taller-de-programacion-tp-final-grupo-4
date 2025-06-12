#include "menu_context.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>

#include "common/event_type.h"

#include "controller/game_controller.h"

#include "command/quit_command.h"

void Context::MenuContext::trigger_buttons(Shared<SDL_Event> event) {
    exit_button.trigger(event);
}

void Context::MenuContext::update_size() {
    background.set_max_size(renderer->GetViewport().GetSize());
    background.set_size(renderer->GetViewport().GetSize());
}

void Context::MenuContext::render() {
    player_renderer.render();

    background.render();
    exit_button.render();
}

void Context::MenuContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        strategy.handle(make_shared<SDL_Event>(placeholder));
    }
}

Context::MenuContext::MenuContext(Weak<Controller::GameController> controller):
Context::BaseContext("menu", controller),
strategy(controller, this),
player_renderer(controller),
background(controller),
exit_button(controller) {
    background.set_background_color(31, 45, 31, 255);
    background.set_draw_background(true);
    background.add_child(&exit_button);
    background.set_horizontal_alignment(0.3);

    exit_button.set_background_color(78, 107, 60, 255);
    exit_button.set_draw_background(true);
    exit_button.set_text("Exit");
    exit_button.set_font_size(16);
    exit_button.set_height(exit_button.get_height() + 8);
    exit_button.set_width(exit_button.get_width() + 8);

    exit_button.set_command(make_unique<Command::QuitCommand>());
}

void Context::MenuContext::handle_event(Shared<Model::Event> event) {
    Model::EventType event_type = event->get_type();
    if (
        event_type == Model::EventType::SWITCH_CONTEXT || 
        event_type == Model::EventType::WINDOW_RESIZE 
    ) {
        update_size();
    }
}
